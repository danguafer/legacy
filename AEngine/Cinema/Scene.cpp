#include "Scene.h"
#include "Object.h"

#include "../Renderers/GraphicsRenderer.h"

using namespace Silexars;
using namespace AEngine;
using namespace Cinema;
using namespace Renderers;

using namespace Graphics::API::Samplers;

Scene::Scene() {
    skybox = 0;
}

void Scene::add(CinemaObject *object) { cObjs.push_back(object); }
void Scene::remove(CinemaObject *object) { cObjs.remove(object); }

uint8 Scene::getType() const { return SCENE; }

Scene::iterator Scene::begin() { return cObjs.begin(); }
Scene::iterator Scene::end() { return cObjs.end(); }
uint32 Scene::size() { return cObjs.size(); }

void Scene::setSkybox(SamplerCube *skybox) { this->skybox = skybox; }
SamplerCube* Scene::getSkybox() const { return skybox; }

#include <Veritas/System/IO/FileSystem/File.h>
#include <Veritas/Graphics/Image/Image.h>
#include <cstring>

// 4 - "SAEF" - Silexars AE File
// 1 - SAEF file type

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace FileSystem;

using namespace Math;

using namespace Graphics;
using namespace API;
using namespace Buffers;
using namespace Samplers;

#include <iostream>
#include <cstdlib>

Scene* Scene::load(const char *path) {
    FileNode node(path);
    File file(&node);

    if (file.getStatus() != File::CONNECTED) return 0;

    char magicNumber[4];
    if (file.read(magicNumber, 4) != 4) return 0;
    if (strncmp(magicNumber, "SAEF", 4)) return 0;

    uint8 type;
    if (file.read(&type, 1) != 1) return 0;
    if (type != 1) return 0;

    Scene *scene = new Scene();

    uint32 nmeshes;
    file.read(&nmeshes, sizeof(nmeshes));

    for (uint32 i = 0; i < nmeshes; i++) {
        uint32 namelen;
        file.read(&namelen, sizeof(namelen));
        char* name = new char[namelen + 1];
        file.read(name, namelen);
        name[namelen] = 0;

        Object::Material *material = 0;

        uint32 albedolen;
        file.read(&albedolen, sizeof(albedolen));
        if (albedolen) {
            char* albedo = new char[albedolen + 1];
            file.read(albedo, albedolen);
            albedo[albedolen] = 0;

            Image *image = Image::load(albedo);
            material = new Object::Material(new Sampler2D(image->getWidth(), image->getHeight(), Sampler2D::RGBA, image->getData()));
            delete image;
            delete[] albedo;
        }

        VertexBuffer* vertices = 0, *normals = 0, *texcoords = 0;

        uint32 nvertices;
        file.read(&nvertices, sizeof(nvertices));

        vec3 *vdata = new vec3[nvertices];
        file.read(vdata, sizeof(vec3)*nvertices);
        vertices = new VertexBuffer(3, nvertices, VertexBuffer::FLOAT32, vdata);
        delete[] vdata;

        file.read(&nvertices, sizeof(nvertices));
        vec3 *ndata = new vec3[nvertices];
        file.read(ndata, sizeof(vec3)*nvertices);
        normals = new VertexBuffer(3, nvertices, VertexBuffer::FLOAT32, ndata);
        delete[] ndata;

        file.read(&nvertices, sizeof(nvertices));
        if (nvertices) {
            vec2 *texcdata = new vec2[nvertices];
            file.read(texcdata, sizeof(vec2)*nvertices);
            texcoords = new VertexBuffer(2, nvertices, VertexBuffer::FLOAT32, texcdata);
            delete[] texcdata;
        }

        uint32 nindices;
        file.read(&nindices, sizeof(nindices));
        uint16* idata = new uint16[nindices];
        file.read(idata, sizeof(uint16)*nindices);
        IndexBuffer* indices = new IndexBuffer(nindices, IndexBuffer::UINT16, idata);

        RenderProgram::VertexArrayObject *vao = new RenderProgram::VertexArrayObject();
        vao->setVertexBuffer(GraphicsRenderer::VERTICES, vertices);
        vao->setVertexBuffer(GraphicsRenderer::NORMALS, normals);
        vao->setVertexBuffer(GraphicsRenderer::TEXCOORDS, texcoords);
        vao->setIndexBuffer(indices);
        Object* obj0 = new Object(material, vao);

        scene->add(obj0);

        obj0->setName(name);

        delete[] name;
    }

    return scene;
}

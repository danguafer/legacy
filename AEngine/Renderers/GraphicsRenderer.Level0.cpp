#include "GraphicsRenderer.Level0.h"

using namespace Silexars;
using namespace AEngine;
using namespace Renderers;
using namespace Cinema;

using namespace Graphics;
using namespace API;
using namespace Buffers;
using namespace Shaders;
using namespace Samplers;

using namespace System::UI;

using namespace Math;

#include <cstdlib>

GraphicsRenderer::Level0::Level0(Window *window) : GraphicsRenderer(window) {
    staticVS = new VertexShader(
        "layout (location = 0) in vec3 vertices;"
        "layout (location = 1) in vec3 normals;"
        "layout (location = 2) in vec2 texcoords;"

        "uniform Camera {"
            "vec3 cameraPosition;"
            "mat4 worldToCamera;"
            "mat4 cameraToScreen;"
        "};"

        "uniform mat4 modelToWorld;"
        "uniform mat3 worldRotation;"

        "varying vec3 normal;"
        "varying vec3 view;"
        "varying vec2 uv;"

        "void main(void) {"
            "gl_Position = vec4(vertices, 1.0);" // Model space
            "gl_Position = modelToWorld * gl_Position;" // World space

            "normal = worldRotation * normals;"
            "view = normalize(gl_Position.xyz - cameraPosition);"
            "uv = texcoords;"

            "gl_Position = worldToCamera * gl_Position;" // Camera space
            "gl_Position = cameraToScreen * gl_Position;" // Screen space
        "}"
    );

    FragmentShader* fs = new FragmentShader(
        "varying vec3 normal;"
        "varying vec2 uv;"

        "uniform sampler2D albedoSample;"

        "void main(void) { gl_FragColor = texture2D(albedoSample, uv); }"
    );
    rp = new RenderProgram(staticVS, fs);

    FragmentShader* skyboxfs = new FragmentShader(
        "uniform samplerCube skybox;"
        "varying vec3 view;"

        "void main(void) { gl_FragColor = textureCube(skybox, view); }"
    );

    skyboxrp = new RenderProgram(staticVS, skyboxfs);

    delete fs;
    delete skyboxfs;
}
GraphicsRenderer::Level0::~Level0() {
    delete rp;
    delete skyboxrp;
    delete staticVS;
}

void GraphicsRenderer::Level0::render(Camera *camera, Scene *scene) {
    rp->uniformBuffer("Camera", camera->ubo);
    skyboxrp->uniformBuffer("Camera", camera->ubo);

    GraphicsRenderer::render(camera, scene);
}

void GraphicsRenderer::Level0::render(Camera *camera, Object *object, mat4 transformation) {
    transformation = mat4::scaling(object->getScale()) * mat4::rotation(object->getRotation()) * mat4::translation(object->getPosition()) * transformation;

    mat3 rotation = transpose(inverse(mat3(transformation)));
    rp->getLocalUniformBuffer()->uniform3x3("worldRotation", (float32*) &rotation);
    rp->getLocalUniformBuffer()->uniform4x4("modelToWorld", (float32*) &transformation);

    rp->sampler("albedoSample", object->getMaterial()->getAlbedo());

    camera->render(rp, object);
}

void GraphicsRenderer::Level0::render(Camera *camera, SamplerCube *skybox) {
    RenderProgram* rp = skyboxrp;

    mat3 rotation = mat3::identity();
    mat4 transformation = mat4::scaling(vec3(-500.0f));

    rp->getLocalUniformBuffer()->uniform3x3("worldRotation", (float32*) &rotation);
    rp->getLocalUniformBuffer()->uniform4x4("modelToWorld", (float32*) &transformation);
    rp->sampler("skybox", skybox);

    camera->render(rp, skybox);
}

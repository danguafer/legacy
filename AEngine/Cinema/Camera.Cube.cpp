#include "Camera.Cube.h"
#include "../Engine.h"

using namespace Silexars;
using namespace AEngine;
using namespace Cinema;

using namespace Math;

using namespace Graphics::API;
using namespace Buffers;
using namespace Samplers;
using namespace Shaders;

Camera::Cube::Cube(uint32 dimension) {
    projection = mat4::perspective(90.0f, 1.0f, 0.1f, 1000.0f);
    cube = new SamplerCube(dimension, SamplerCube::RGBA);

    nx = new FrameBuffer; nx->setColorBuffer(cube, SamplerCube::NEGATIVE_X); nx->setDepthBuffer((Sampler2D*) FrameBuffer::INTERNAL);
    px = new FrameBuffer; px->setColorBuffer(cube, SamplerCube::POSITIVE_X); px->setDepthBuffer((Sampler2D*) FrameBuffer::INTERNAL);
    ny = new FrameBuffer; ny->setColorBuffer(cube, SamplerCube::NEGATIVE_Y); ny->setDepthBuffer((Sampler2D*) FrameBuffer::INTERNAL);
    py = new FrameBuffer; py->setColorBuffer(cube, SamplerCube::POSITIVE_Y); py->setDepthBuffer((Sampler2D*) FrameBuffer::INTERNAL);
    nz = new FrameBuffer; nz->setColorBuffer(cube, SamplerCube::NEGATIVE_Z); nz->setDepthBuffer((Sampler2D*) FrameBuffer::INTERNAL);
    pz = new FrameBuffer; pz->setColorBuffer(cube, SamplerCube::POSITIVE_Z); pz->setDepthBuffer((Sampler2D*) FrameBuffer::INTERNAL);
}

Camera::Cube::~Cube() {
    delete nx;
    delete px;
    delete ny;
    delete py;
    delete nz;
    delete pz;
    delete cube;
}

uint8 Camera::Cube::getCameraType() const { return CUBE; }

void Camera::Cube::clear() {
    Context::getCurrent()->getClearProgram()->clear(nx);
    Context::getCurrent()->getClearProgram()->clear(px);
    Context::getCurrent()->getClearProgram()->clear(ny);
    Context::getCurrent()->getClearProgram()->clear(py);
    Context::getCurrent()->getClearProgram()->clear(nz);
    Context::getCurrent()->getClearProgram()->clear(pz);
}
void Camera::Cube::render(Scene *scene) { Engine::getCurrent()->getGraphicsRenderer()->render(this, scene); }
void Camera::Cube::display(FrameBuffer *framebuffer) { Engine::getCurrent()->getGraphicsRenderer()->display(this, framebuffer); }

SamplerCube* Camera::Cube::getSamplerCube() const { return cube; }

void Camera::Cube::render(RenderProgram *rp, Object *object) {
    mat4 worldToCamera = mat4::translation(-position) * mat4::lookAt(vec3(1.0, 0.0, 0.0), vec3(0.0, -1.0, 0.0));
    ubo->uniform4x4("worldToCamera", (float32*) &worldToCamera);
    rp->render(px, RenderProgram::TRIANGLES, object->getVAO());

    worldToCamera = mat4::translation(-position) * mat4::lookAt(vec3(-1.0, 0.0, 0.0), vec3(0.0, -1.0, 0.0));
    ubo->uniform4x4("worldToCamera", (float32*) &worldToCamera);
    rp->render(nx, RenderProgram::TRIANGLES, object->getVAO());

    worldToCamera = mat4::translation(-position) * mat4::lookAt(vec3(0.0, 1.0, 0.0), vec3(0.0, 0.0, 1.0));
    ubo->uniform4x4("worldToCamera", (float32*) &worldToCamera);
    rp->render(py, RenderProgram::TRIANGLES, object->getVAO());

    worldToCamera = mat4::translation(-position) * mat4::lookAt(vec3(0.0, -1.0, 0.0), vec3(0.0, 0.0, -1.0));
    ubo->uniform4x4("worldToCamera", (float32*) &worldToCamera);
    rp->render(ny, RenderProgram::TRIANGLES, object->getVAO());

    worldToCamera = mat4::translation(-position) * mat4::lookAt(vec3(0.0, 0.0, 1.0), vec3(0.0, -1.0, 0.0));
    ubo->uniform4x4("worldToCamera", (float32*) &worldToCamera);
    rp->render(pz, RenderProgram::TRIANGLES, object->getVAO());

    worldToCamera = mat4::translation(-position) * mat4::lookAt(vec3(0.0, 0.0, -1.0), vec3(0.0, -1.0, 0.0));
    ubo->uniform4x4("worldToCamera", (float32*) &worldToCamera);
    rp->render(nz, RenderProgram::TRIANGLES, object->getVAO());

}

void Camera::Cube::render(RenderProgram *rp, SamplerCube *skybox) {
    RenderProgram::VertexArrayObject *vao = Context::getCurrent()->getCube();

    mat4 worldToCamera = mat4::lookAt(vec3(1.0, 0.0, 0.0), vec3(0.0, -1.0, 0.0));
    ubo->uniform4x4("worldToCamera", (float32*) &worldToCamera);
    rp->render(px, RenderProgram::TRIANGLES, vao);

    worldToCamera = mat4::lookAt(vec3(-1.0, 0.0, 0.0), vec3(0.0, -1.0, 0.0));
    ubo->uniform4x4("worldToCamera", (float32*) &worldToCamera);
    rp->render(nx, RenderProgram::TRIANGLES, vao);

    worldToCamera = mat4::lookAt(vec3(0.0, 1.0, 0.0), vec3(0.0, 0.0, 1.0));
    ubo->uniform4x4("worldToCamera", (float32*) &worldToCamera);
    rp->render(py, RenderProgram::TRIANGLES, vao);

    worldToCamera = mat4::lookAt(vec3(0.0, -1.0, 0.0), vec3(0.0, 0.0, -1.0));
    ubo->uniform4x4("worldToCamera", (float32*) &worldToCamera);
    rp->render(ny, RenderProgram::TRIANGLES, vao);

    worldToCamera = mat4::lookAt(vec3(0.0, 0.0, 1.0), vec3(0.0, -1.0, 0.0));
    ubo->uniform4x4("worldToCamera", (float32*) &worldToCamera);
    rp->render(pz, RenderProgram::TRIANGLES, vao);

    worldToCamera = mat4::lookAt(vec3(0.0, 0.0, -1.0), vec3(0.0, -1.0, 0.0));
    ubo->uniform4x4("worldToCamera", (float32*) &worldToCamera);
    rp->render(nz, RenderProgram::TRIANGLES, vao);
}

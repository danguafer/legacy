#include "Camera.Mono.h"
#include "../Engine.h"

using namespace Silexars;
using namespace AEngine;
using namespace Cinema;

using namespace Math;

using namespace Graphics::API;
using namespace Buffers;
using namespace Samplers;
using namespace Shaders;

Camera::Mono::Mono(uint32 width, uint32 height, float32 fov) {
    this->width = width;
    this->height = height;
    projection = mat4::perspective(fov, (float32) width/(float32) height, 0.1f, 1000.0f);
    fb = new FrameBuffer(new Sampler2D(width, height, Sampler2D::RGBA), (Sampler2D*) FrameBuffer::INTERNAL, 0); // let GraphicsRenderer create the GBuffer object
}

Camera::Mono::~Mono() {
    delete fb->getColorBuffer(0);
    delete fb;
}

uint32 Camera::Mono::getWidth() const { return width; }
uint32 Camera::Mono::getHeight() const { return height; }

void Camera::Mono::clear() { Context::getCurrent()->getClearProgram()->clear(fb); }
void Camera::Mono::render(Scene *scene) { Engine::getCurrent()->getGraphicsRenderer()->render(this, scene); }

Sampler2D* Camera::Mono::getSampler2D() const { return fb->getColorBuffer(0); }
uint8 Camera::Mono::getCameraType() const { return MONO; }

void Camera::Mono::display(FrameBuffer *framebuffer) { Engine::getCurrent()->getGraphicsRenderer()->display(this, framebuffer); }

void Camera::Mono::render(RenderProgram *rp, Object *object) { rp->render(fb, RenderProgram::TRIANGLES, object->getVAO()); }
void Camera::Mono::render(RenderProgram *rp, SamplerCube *skybox) {
    rp->render(fb, RenderProgram::TRIANGLES, Context::getCurrent()->getCube());
}


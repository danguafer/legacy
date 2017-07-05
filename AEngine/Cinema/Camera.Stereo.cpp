#include "Camera.Stereo.h"
#include "../Engine.h"

using namespace Silexars;
using namespace AEngine;
using namespace Cinema;

using namespace Math;

using namespace Graphics::API;
using namespace Buffers;
using namespace Samplers;
using namespace Shaders;

Camera::Stereo::Stereo(uint32 width, uint32 height, float32 fov) {
    projection = mat4::perspective(fov, (width/2.0f)/(float32) height, 0.1f, 1000.0f);

    left = new FrameBuffer(new Sampler2D(width/2, height, Sampler2D::RGBA), (Sampler2D*) FrameBuffer::INTERNAL, 0);
    right = new FrameBuffer(new Sampler2D(width/2, height, Sampler2D::RGBA), (Sampler2D*) FrameBuffer::INTERNAL, 0);
    setPupillaryDistance(0.006f);
}

Camera::Stereo::~Stereo() {
    delete left;
    delete right;
}

uint8 Camera::Stereo::getCameraType() const { return STEREO; }

void Camera::Stereo::clear() {
    Context::getCurrent()->getClearProgram()->clear(left);
    Context::getCurrent()->getClearProgram()->clear(right);
}
void Camera::Stereo::render(Scene *scene) { Engine::getCurrent()->getGraphicsRenderer()->render(this, scene); }
void Camera::Stereo::display(FrameBuffer *framebuffer) { Engine::getCurrent()->getGraphicsRenderer()->display(this, framebuffer); }

Sampler2D* Camera::Stereo::getLeftSampler2D() const { return left->getColorBuffer(0); }
Sampler2D* Camera::Stereo::getRightSampler2D() const { return right->getColorBuffer(0); }

void Camera::Stereo::setPupillaryDistance(float32 distance) { pupillaryDistance = distance; }
float32 Camera::Stereo::getPupillaryDistance() const { return pupillaryDistance; }

#include <iostream>
void Camera::Stereo::render(RenderProgram *rp, Object *object) {
    mat4 rotation = mat4::rotation(conjugate(this->rotation));

    vec3 pupillaryOffset = vec3(getPupillaryDistance(), 0.0f, 0.0f);

    mat4 worldToCamera = mat4::translation(-position) * rotation * mat4::translation(pupillaryOffset);
    ubo->uniform4x4("worldToCamera", (float32*) &worldToCamera);
    rp->render(left, RenderProgram::TRIANGLES, object->getVAO());

    worldToCamera = mat4::translation(-position) * rotation * mat4::translation(-pupillaryOffset);
    ubo->uniform4x4("worldToCamera", (float32*) &worldToCamera);
    rp->render(right, RenderProgram::TRIANGLES, object->getVAO());
}

void Camera::Stereo::render(RenderProgram *rp, SamplerCube *skybox) {
    RenderProgram::VertexArrayObject *vao = Context::getCurrent()->getCube();

    rp->render(left, RenderProgram::TRIANGLES, vao);
    rp->render(right, RenderProgram::TRIANGLES, vao);
}


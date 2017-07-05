#include "GraphicsRenderer.h"

#include "../Cinema/Object.h"
#include <Veritas/Graphics/Image/Image.h>

using namespace Silexars;

using namespace Math;

using namespace System::UI;
using namespace Graphics;
using namespace API;
using namespace Shaders;
using namespace Samplers;
using namespace Buffers;

using namespace AEngine;
using namespace Renderers;
using namespace Cinema;

void makeCurrent(void* data) { ((GLContext*) data)->makeCurrent(); }
void swapBuffers(void* data) { ((GLContext*) data)->swapBuffers(); }

GraphicsRenderer::GraphicsRenderer(Window *window) {
    ctx = new Context(makeCurrent, swapBuffers, window->getView()->getGLContext());

    VertexShader *vs = new VertexShader("layout (location = 0) in vec2 vertices; varying vec2 uv; void main(void) { gl_Position = vec4(vertices, 1.0, 1.0); uv = (gl_Position.xy + 1.0)/2.0; }");
    FragmentShader *fs = new FragmentShader("uniform sampler2D camera; varying vec2 uv; void main(void) { gl_FragColor = vec4(texture2D(camera, uv).rgb, 1.0); }");
    displayMono = new RenderProgram(vs, fs);
    displayMono->setDepthTesting(false);
    displayMono->setFaceCulling(false);
    delete vs; delete fs;

    vs = new VertexShader("layout (location = 0) in vec2 vertices; varying vec2 uv; uniform float offset; void main(void) { gl_Position = vec4(vertices, 1.0, 1.0); uv = (gl_Position.xy + 1.0)/2.0; gl_Position.x = gl_Position.x * 0.5 + offset; }");
    fs = new FragmentShader("uniform sampler2D camera; varying vec2 uv; void main(void) { gl_FragColor = vec4(texture2D(camera, uv).rgb, 1.0); }");
    displayStereo = new RenderProgram(vs, fs);
    displayStereo->setDepthTesting(false);
    displayStereo->setFaceCulling(false);
    delete vs; delete fs;

    #warning Aspect not implemented on displayCube
    vs = new VertexShader("layout (location = 0) in vec2 vertices; varying vec3 view; uniform mat3 rotation; void main(void) { gl_Position = vec4(vertices, 1.0, 1.0); view = rotation * normalize(vec3(gl_Position.xy, -2.0)); }");
    fs = new FragmentShader("uniform samplerCube camera; varying vec3 view; void main(void) { gl_FragColor = vec4(textureCube(camera, view).rgb, 1.0); }");
    displayCube = new RenderProgram(vs, fs);
    displayCube->setDepthTesting(false);
    displayCube->setFaceCulling(false);
    delete vs; delete fs;
}

GraphicsRenderer::~GraphicsRenderer() {
    delete ctx;

    delete displayMono;
    delete displayStereo;
    delete displayCube;
}

void GraphicsRenderer::render(Camera *camera, Scene *scene) {
    mat4 worldToCamera = mat4::translation(-camera->position) * mat4::rotation(conjugate(camera->rotation));
    camera->ubo->uniform4x4("cameraToScreen", (float32*) &camera->projection);
    camera->ubo->uniform3("cameraPosition", (float32*) &camera->position);

    if (scene->skybox) render(camera, scene->skybox);

    camera->ubo->uniform4x4("worldToCamera", (float32*) &worldToCamera);
    render(camera, scene, mat4::identity());
}

void GraphicsRenderer::render(Camera *camera, Scene *scene, mat4 transformation) {
    transformation = mat4::scaling(scene->getScale()) * mat4::rotation(scene->getRotation()) * mat4::translation(scene->getPosition()) * transformation;

    iterate(Scene, scene) {
        CinemaObject *obj = *iterator;
        switch (obj->getType()) {
            case CinemaObject::OBJECT: render(camera, (Object*) obj, transformation); break;
            case CinemaObject::SCENE: render(camera, (Scene*) obj, transformation); break;
        }
    }
}

void GraphicsRenderer::display(Camera::Mono *camera, FrameBuffer *framebuffer) {
    displayMono->sampler("camera", camera->getSampler2D());

    displayMono->render(framebuffer, RenderProgram::TRIANGLES, ctx->getQuad());
    ctx->swapBuffers(framebuffer);
}

void GraphicsRenderer::display(Camera::Cube *camera, FrameBuffer *framebuffer) {
    mat3 rotation = mat3::rotation(camera->rotation);

    displayCube->sampler("camera", camera->getSamplerCube());
    displayCube->getLocalUniformBuffer()->uniform3x3("rotation", (float32*) &rotation);

    displayCube->render(framebuffer, RenderProgram::TRIANGLES, ctx->getQuad());
    ctx->swapBuffers(framebuffer);
}

void GraphicsRenderer::display(Camera::Stereo *camera, FrameBuffer *framebuffer) {
    displayStereo->sampler("camera", camera->getLeftSampler2D());
    displayStereo->getLocalUniformBuffer()->uniform("offset", -0.5f);
    displayStereo->render(framebuffer, RenderProgram::TRIANGLES, ctx->getQuad());

    displayStereo->sampler("camera", camera->getRightSampler2D());
    displayStereo->getLocalUniformBuffer()->uniform("offset", 0.5f);
    displayStereo->render(framebuffer, RenderProgram::TRIANGLES, ctx->getQuad());

    ctx->swapBuffers(framebuffer);
}

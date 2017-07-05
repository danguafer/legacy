#include "Canvas3D.h"

using namespace Silexars;
using namespace Graphics;
using namespace Canvas;
using namespace API;
using namespace Buffers;
using namespace Shaders;
using namespace Math;

#define GLSL(...) #__VA_ARGS__

Canvas3D::Canvas3D(API::Context *ctx, FrameBuffer *framebuffer) {
    this->ctx = ctx;

    vs = new VertexShader(GLSL(
        layout(location = 0) in vec3 vertices;
        layout(location = 1) in vec3 normals;
        layout(location = 2) in vec2 texcoords;

        uniform mat3 rotation;
        uniform mat4 projection;
        uniform mat4 transformation;
        uniform vec3 position;
        uniform vec3 dimension;

        varying vec3 normal;
        varying vec3 point;
        varying vec2 uv;

        void main(void) {
            vec3 vertex = vertices * dimension + position;
            gl_Position = transformation * vec4(vertex, 1.0);
            point = gl_Position.xyz;
            gl_Position = projection * gl_Position;
            normal = rotation * normals;
            uv = texcoords;
        }
    ));
    FragmentShader *colorfs = new FragmentShader(GLSL(
        uniform vec4 color;
        void main(void) { gl_FragColor = color; }
    ));

    colorProgram = new RenderProgram(vs, colorfs);

    delete colorfs;

    float32 boxvertices[] = { 0.0f, 0.0f, 0.0f,0.0f, 0.0f, 1.0f,0.0f, 1.0f, 0.0f,0.0f, 1.0f, 1.0f,1.0f, 0.0f, 0.0f,1.0f, 0.0f, 1.0f,1.0f, 1.0f, 0.0f,1.0f, 1.0f, 1.0f,0.0f, 0.0f, 0.0f,0.0f, 0.0f, 1.0f,1.0f, 0.0f, 0.0f,1.0f, 0.0f, 1.0f,0.0f, 1.0f, 0.0f,0.0f, 1.0f, 1.0f,1.0f, 1.0f, 0.0f,1.0f, 1.0f, 1.0f,0.0f, 0.0f, 1.0f,0.0f, 1.0f, 1.0f,1.0f, 0.0f, 1.0f,1.0f, 1.0f, 1.0f,0.0f, 0.0f, 0.0f,0.0f, 1.0f, 0.0f,1.0f, 0.0f, 0.0f,1.0f, 1.0f, 0.0f};
    float32 boxnormals[] = { -1.0f, 0.0f, 0.0f,-1.0f, 0.0f, 0.0f,-1.0f, 0.0f, 0.0f,-1.0f, 0.0f, 0.0f,1.0f, 0.0f, 0.0f,1.0f, 0.0f, 0.0f,1.0f, 0.0f, 0.0f,1.0f, 0.0f, 0.0f,0.0f, -1.0f, 0.0f,0.0f, -1.0f, 0.0f,0.0f, -1.0f, 0.0f,0.0f, -1.0f, 0.0f,0.0f,  1.0f, 0.0f,0.0f,  1.0f, 0.0f,0.0f,  1.0f, 0.0f,0.0f,  1.0f, 0.0f,0.0f,  0.0f,  1.0f,0.0f,  0.0f,  1.0f,0.0f,  0.0f,  1.0f,0.0f,  0.0f,  1.0f,0.0f,  0.0f, -1.0f,0.0f,  0.0f, -1.0f,0.0f,  0.0f, -1.0f,0.0f,  0.0f, -1.0f};
    float32 boxtexcoords[] = { 0.0f, 0.0f,0.0f, 1.0f,1.0f, 0.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f, 1.0f,1.0f, 0.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f, 1.0f,1.0f, 0.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f, 1.0f,1.0f, 0.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f, 1.0f,1.0f, 0.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f, 1.0f,1.0f, 0.0f,1.0f, 1.0f};
    uint8 trianglesdata[] = { 0, 1, 3, 0, 3, 2,4, 7, 5, 4, 6, 7,8, 11, 9, 8, 10, 11,12, 13, 15, 12, 15, 14,16, 19, 17, 16, 18, 19,20, 21, 23, 20, 23, 22};
    uint8 linesdata[] = { 0, 1, 0, 4, 5, 1, 5, 4, 2, 6, 2, 3, 7, 3, 7, 6, 1, 3, 5, 7, 0, 2, 4, 6 }; // vertices data has changed and linesdata wasn't tested, but it seems to be working without any kind of change.

    boxTriangles = new RenderProgram::VertexArrayObject();
    boxTriangles->setVertexBuffer(0, new VertexBuffer(3, sizeof(boxvertices)/sizeof(float32)/3, VertexBuffer::FLOAT32, boxvertices));
    boxTriangles->setVertexBuffer(1, new VertexBuffer(3, sizeof(boxnormals)/sizeof(float32)/3, VertexBuffer::FLOAT32, boxnormals));
    boxTriangles->setVertexBuffer(2, new VertexBuffer(2, sizeof(boxtexcoords)/sizeof(float32)/2, VertexBuffer::FLOAT32, boxtexcoords));

    boxTriangles->setIndexBuffer(new IndexBuffer(sizeof(trianglesdata), IndexBuffer::UINT8, trianglesdata));
    boxLines->setIndexBuffer(new IndexBuffer(sizeof(linesdata), IndexBuffer::UINT8, linesdata));

    float32 linevertices[] = { 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f };
    line = new RenderProgram::VertexArrayObject();
    line->setVertexBuffer(0, new VertexBuffer(3, 2, VertexBuffer::FLOAT32, linevertices));

    stateStack.push(new State());
    stateStack.top()->transformation = mat4::identity();

    setFillColor(vec4(0.0));
    setStrokeColor(vec4(0.0));
    setFrameBuffer(framebuffer);
}

Canvas3D::~Canvas3D() {
    delete colorProgram;

    delete boxTriangles->getVertexBuffer(0);
    delete boxTriangles->getVertexBuffer(1);
    delete boxTriangles->getVertexBuffer(2);
    delete boxTriangles->getIndexBuffer();
    delete boxLines->getIndexBuffer();
    delete boxTriangles;
    delete boxLines;

    delete line->getVertexBuffer(0);
    delete line;

    delete vs;

    while (stateStack.size()) {
        delete stateStack.top();
        stateStack.pop();
    }
}

void Canvas3D::setFrameBuffer(FrameBuffer *fb) {
    this->fb = fb;
    stateStack.top()->projection = mat4::perspective(45.0f, (float32) fb->getWidth()/(float32) fb->getHeight(), 1.0f, 1000.0f);
    colorProgram->getLocalUniformBuffer()->uniform4x4("projection", (float32*) &stateStack.top()->projection);
}
FrameBuffer* Canvas3D::getFrameBuffer() const { return fb; }
VertexShader* Canvas3D::getVertexShader() const { return vs; }

void Canvas3D::setFillColor(const vec4& color) { stateStack.top()->fillColor = color; }
const vec4& Canvas3D::getFillColor() const { return stateStack.top()->fillColor; }

void Canvas3D::setStrokeColor(const vec4& color) { stateStack.top()->strokeColor = color; }
const vec4& Canvas3D::getStrokeColor() const { return stateStack.top()->strokeColor; }

void Canvas3D::clear() { Context::getCurrent()->getClearProgram()->clear(fb); }

void Canvas3D::fillBox(const vec3 &position, const vec3 &dimension) { fillBox(colorProgram, position, dimension); }
void Canvas3D::fillBox(RenderProgram *renderProgram, const vec3 &position, const vec3 &dimension) {
    renderProgram->getLocalUniformBuffer()->uniform3("position", (float32*) &position);
    renderProgram->getLocalUniformBuffer()->uniform3("dimension", (float32*) &dimension);
    renderProgram->getLocalUniformBuffer()->uniform4("color", (float32*) &stateStack.top()->fillColor);

    mat3 rotation = stateStack.top()->transformation;
    rotation = transpose(inverse(rotation));
    renderProgram->getLocalUniformBuffer()->uniform3x3("rotation", (float32*) &rotation);
    renderProgram->getLocalUniformBuffer()->uniform4x4("transformation", (float32*) &stateStack.top()->transformation);
    renderProgram->getLocalUniformBuffer()->uniform4x4("projection", (float32*) &stateStack.top()->projection);
    renderProgram->render(fb, RenderProgram::TRIANGLES, boxTriangles);
}

void Canvas3D::strokeBox(const vec3 &position, const vec3 &dimension) {
    colorProgram->getLocalUniformBuffer()->uniform3("position", (float32*) &position);
    colorProgram->getLocalUniformBuffer()->uniform3("dimension", (float32*) &dimension);
    colorProgram->getLocalUniformBuffer()->uniform4("color", (float32*) &stateStack.top()->strokeColor);
    colorProgram->getLocalUniformBuffer()->uniform4x4("transformation", (float32*) &stateStack.top()->transformation);
    colorProgram->render(fb, RenderProgram::LINES, boxLines);
}

void Canvas3D::strokeLine(const vec3 &p0, const vec3 &p1) {
    vec3 position = p0;
    vec3 dimension = p1 - p0;

    colorProgram->getLocalUniformBuffer()->uniform3("position", (float32*) &position);
    colorProgram->getLocalUniformBuffer()->uniform3("dimension", (float32*) &dimension);
    colorProgram->getLocalUniformBuffer()->uniform4("color", (float32*) &stateStack.top()->strokeColor);
    colorProgram->getLocalUniformBuffer()->uniform4x4("transformation", (float32*) &stateStack.top()->transformation);
    colorProgram->render(fb, RenderProgram::LINES, line);
}

void Canvas3D::setTransformation(const mat4 &transformation) { stateStack.top()->transformation = transformation; }
const mat4& Canvas3D::getTransformation() { return stateStack.top()->transformation; }

void Canvas3D::scale(const vec3& scaling) { stateStack.top()->transformation = mat4::scaling(scaling) * stateStack.top()->transformation; }
void Canvas3D::translate(const vec3 &translation) { stateStack.top()->transformation = mat4::translation(translation) * stateStack.top()->transformation; }
void Canvas3D::rotateX(float32 a) { stateStack.top()->transformation = mat4::xRotation(-a) * stateStack.top()->transformation; }
void Canvas3D::rotateY(float32 a) { stateStack.top()->transformation = mat4::yRotation(-a) * stateStack.top()->transformation; }
void Canvas3D::rotateZ(float32 a) { stateStack.top()->transformation = mat4::zRotation(-a) * stateStack.top()->transformation; }

void Canvas3D::save() {
    State *state = new State();
    *state = *stateStack.top();
    stateStack.push(state);
}

void Canvas3D::restore() {
    if (stateStack.size() > 1) {
        State *state = stateStack.top();
        stateStack.pop();
        delete state;
    }
}

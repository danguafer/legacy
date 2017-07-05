#include "ClearProgram.h"
#include "Context.h"
#include "third-party/glLoader/glLoader.h"

using namespace Silexars;
using namespace Graphics;
using namespace API;
using namespace Math;

ClearProgram::ClearProgram() {
    color = vec4(0.0f);
    depth = 1.0f;
    stencil = 0;
    iscolorblending = false;
}

ClearProgram::~ClearProgram() {}

void ClearProgram::setColor(vec4 color) { this->color = color; }
vec4 ClearProgram::getColor() const { return color; }

void ClearProgram::setDepth(float32 depth) { this->depth = depth; }
float32 ClearProgram::getDepth() const { return depth; }

void ClearProgram::setStencil(int32 stencil) { this->stencil = stencil; }
int32 ClearProgram::getStencil() const { return stencil; }

void ClearProgram::clear(Buffers::FrameBuffer *fb, uint32 flags) {
    Context *ctx = Context::getCurrent();
    if (COLOR_BUFFER_BIT&flags) ctx->GPUClearProgram.setColor(color);
    if (DEPTH_BUFFER_BIT&flags) ctx->GPUClearProgram.setDepth(depth);
    if (STENCIL_BUFFER_BIT&flags) ctx->GPUClearProgram.setStencil(stencil);
    fb->use();
    glClear(flags);
}

ClearProgram::GPU::GPU() {
    color = vec4(0.0);
    depth = 1.0f;
    stencil = 0;
}
void ClearProgram::GPU::setColor(vec4 color) {
    if (this->color != color) {
        this->color  = color;
        glClearColor(color.x, color.y, color.z, color.w);
    }
}
void ClearProgram::GPU::setDepth(float32 depth) {
    if (this->depth != depth) {
        this->depth  = depth;
        glClearDepthf(depth);
    }
}
void ClearProgram::GPU::setStencil(int32 stencil) {
    if (this->stencil != stencil) {
        this->stencil  = stencil;
        glClearStencil(stencil);
    }
}

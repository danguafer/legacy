#include "RenderProgram.h"
#include "third-party/glLoader/glLoader.h"
#include "Context.h"
#include <Veritas/Data/String.h>

using namespace Silexars;
using namespace Graphics::API;
using namespace Shaders;
using namespace Samplers;
using namespace Buffers;
using namespace Data;

RenderProgram::RenderProgram(VertexShader *vs, GeometryShader *gs, FragmentShader *fs) { CRenderProgram(vs, gs, fs); }
RenderProgram::RenderProgram(VertexShader *vs, FragmentShader *fs) { CRenderProgram(vs, 0, fs); }

void RenderProgram::CRenderProgram(VertexShader *vs, GeometryShader *gs, FragmentShader *fs) {
    quantity = 0;
    this->vs = vs;
    this->gs = gs;
    this->fs = fs;
    if (vs) glAttachShader((GLuint) id, (GLuint) vs->id);
    if (gs) glAttachShader((GLuint) id, (GLuint) gs->id);
    if (fs) glAttachShader((GLuint) id, (GLuint) fs->id);

    for (uint32 i = 0; i < vs->nInLocations; i++) glBindAttribLocation((GLuint) id, vs->inLocations[i]->index, vs->inLocations[i]->name);

    link();

    setDepthTesting(true);
    setFaceCulling(true);
    setColorBlending(false);

    setColorRendering(true);
    setDepthRendering(true);
    setStencilRendering(true);
}

VertexShader*   RenderProgram::getVertexShader() const   { return vs; }
GeometryShader* RenderProgram::getGeometryShader() const { return gs; }
FragmentShader* RenderProgram::getFragmentShader() const { return fs; }

void RenderProgram::setDepthTesting(bool b) { depthtesting = b; }
bool RenderProgram::isDepthTesting() const { return depthtesting; }

void RenderProgram::setFaceCulling(bool b) { faceculling = b; }
bool RenderProgram::isFaceCulling() const { return faceculling; }

void RenderProgram::setColorBlending(bool b) { colorblending = b; }
bool RenderProgram::isColorBlending() const { return colorblending; }

void RenderProgram::setColorRendering(bool b) { colorrendering = b; }
bool RenderProgram::isColorRendering() const { return colorrendering; }

void RenderProgram::setDepthRendering(bool b) { depthrendering = b; }
bool RenderProgram::isDepthRendering() const { return depthrendering; }

void RenderProgram::setStencilRendering(bool b) { stencilrendering = b; }
bool RenderProgram::isStencilRendering() const { return stencilrendering; }

void RenderProgram::sampler(int32 uniform, Sampler *sampler) {
    if (uniform < 0) return;
    samplers.set(uniform, sampler, LocationBinding::READ_ONLY);
}
void RenderProgram::sampler(const char *s, Sampler *smp) { sampler(getLocalUniformBuffer()->getUniformLocation(s), smp); }

void RenderProgram::render(FrameBuffer *fb, uint32 primitive, VertexArrayObject *vao) {
    Context *ctx = Context::getCurrent();
    fb->use();
    use();

    if (fb->isMultisampled() != Context::current->isMultisampling) {
        Context::current->isMultisampling = fb->isMultisampled();
        if (fb->isMultisampled()) glEnable(GL_MULTISAMPLE);
        else                      glDisable(GL_MULTISAMPLE);
    }

    ctx->GPURenderProgram.setDepthTesting(isDepthTesting());
    ctx->GPURenderProgram.setFaceCulling(isFaceCulling());
    ctx->GPURenderProgram.setColorBlending(isColorBlending());
    ctx->GPURenderProgram.setColorRendering(isColorRendering());
    ctx->GPURenderProgram.setDepthRendering(isDepthRendering());
    ctx->GPURenderProgram.setStencilRendering(isStencilRendering());

    for (uint32 i = 0; i < samplers.nbindings; i++) {
        ((Sampler*) samplers.bindings[i].object)->use(i + 1);
        getLocalUniformBuffer()->uniform(samplers.bindings[i].location, (int32) i + 1);
    }

    vao->use();
    if (vao->ib) glDrawElements(primitive, vao->ib->getQuantity(), vao->ib->format, 0);
    else glDrawArrays(primitive, 0, vao->vbs[0]->getQuantity());
}


RenderProgram::GPU::GPU() {
    depthtesting = false;
    faceculling = false;
    colorblending = false;

    colorrendering = true;
    depthrendering = true;
    stencilrendering = true;
}

void RenderProgram::GPU::setDepthTesting(bool b) {
    if (depthtesting != b) {
        depthtesting  = b;
        (b ? glEnable : glDisable)(GL_DEPTH_TEST);
    }
}

void RenderProgram::GPU::setFaceCulling(bool b) {
    if (faceculling != b) {
        faceculling  = b;
        (b ? glEnable : glDisable)(GL_CULL_FACE);
    }
}

void RenderProgram::GPU::setColorBlending(bool b) {
    if (colorblending != b) {
        colorblending  = b;
        (b ? glEnable : glDisable)(GL_BLEND);
    }
}

void RenderProgram::GPU::setColorRendering(bool b) {
    if (colorrendering != b) {
        colorrendering  = b;
        if (b) glColorMask(0xFF, 0xFF, 0xFF, 0xFF);
        else   glColorMask(0x00, 0x00, 0x00, 0x00);
    }
}

void RenderProgram::GPU::setDepthRendering(bool b) {
    if (depthrendering != b) {
        depthrendering  = b;
        if (b) glDepthMask(0xFF);
        else   glDepthMask(0x00);
    }
}

void RenderProgram::GPU::setStencilRendering(bool b) {
    if (stencilrendering != b) {
        stencilrendering  = b;
        if (b) glStencilMask(0xFF);
        else   glStencilMask(0x00);
    }
}

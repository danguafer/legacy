//! Dirty.
//! Incomplete.
/*
 * Lacks consistency check for multisampling / non-multisampling.
 * Lacks proper ::draw(fb) implementation for GLES
 */

#include "FrameBuffer.h"
#include "../Context.h"

#include "../third-party/glLoader/glLoader.h"

using namespace Silexars;
using namespace Graphics::API;
using namespace Buffers;
using namespace Samplers;
using namespace Math;

const Sampler2D* FrameBuffer::INTERNAL = (Sampler2D*) 1;

FrameBuffer::FrameBuffer(uint32 width, uint32 height) {
    this->width = width;
    this->height = height;
    id = 0;
    cb = 0;
    db = 0;
    sb = 0;
    dbInternal = false;
    sbInternal = false;
    ismultisampled = false;
}

FrameBuffer::FrameBuffer() {
    width = height = 0;

    ismultisampled = false;

    id = 0;
    cb = 0;
    db = 0;
    sb = 0;

    dbInternal = false;
    sbInternal = false;

    glGenFramebuffers(1, (GLuint*) &id);
}

FrameBuffer::FrameBuffer(Sampler2D *cb, Sampler2D *db, Sampler2D *sb) {
    width = height = 0;

    ismultisampled = false;

    id = 0;
    this->cb = 0;
    this->db = 0;
    this->sb = 0;

    dbInternal = false;
    sbInternal = false;

    glGenFramebuffers(1, (GLuint*) &id);
    if (cb) setColorBuffer(cb);
    if (db) setDepthBuffer(db);
    if (sb) setStencilBuffer(sb);
}

FrameBuffer::FrameBuffer(Multisampler2D *cb, Multisampler2D *db, Multisampler2D *sb) {
    width = height = 0;

    id = 0;
    this->cb = 0;
    this->db = 0;
    this->sb = 0;

    ismultisampled = false;

    dbInternal = false;
    sbInternal = false;

    glGenFramebuffers(1, (GLuint*) &id);
    if (cb) setColorBuffer(cb);
    if (db) setDepthBuffer(db);
    if (sb) setStencilBuffer(sb);
}

FrameBuffer::~FrameBuffer() {
    glDeleteFramebuffers(1, (GLuint*) &id);
    if (dbInternal) glDeleteRenderbuffers(1, (GLuint*) &db);
    if (sbInternal) glDeleteRenderbuffers(1, (GLuint*) &db);
}

bool FrameBuffer::isMultisampled() const { return ismultisampled; }

void FrameBuffer::use() {
    if (Context::current->boundFrameBuffer != this) {
        Context::current->boundFrameBuffer  = this;
        glBindFramebuffer(GL_FRAMEBUFFER, (GLuint) id);
        glViewport(0, 0, getWidth(), getHeight());
    }
}

Sampler2D* FrameBuffer::getColorBuffer(uint8 index) const { return cb; }
Sampler2D* FrameBuffer::getDepthBuffer() const { return dbInternal ? (Sampler2D*) INTERNAL : db; }
Sampler2D* FrameBuffer::getStencilBuffer() const { return sbInternal ? (Sampler2D*) INTERNAL : sb; }

vec2 FrameBuffer::getDimension() const { return vec2(width, height); }
uint32 FrameBuffer::getWidth() { return width; }
uint32 FrameBuffer::getHeight() { return height; }

void FrameBuffer::setColorBuffer(Sampler1D *cb) { setColorBuffer((Sampler2D*) cb); }
void FrameBuffer::setDepthBuffer(Sampler1D *db) { setDepthBuffer((Sampler2D*) cb); }
void FrameBuffer::setStencilBuffer(Sampler1D *sb) { setStencilBuffer((Sampler2D*) cb); }

void FrameBuffer::setColorBuffer(Multisampler2D *cb, uint8 index) {
    ismultisampled = true;
    use();
    this->cb = (Sampler2D*) cb;
    width = cb->getWidth();
    height = cb->getHeight();
    #ifdef OPENGLES
    glFramebufferTexture2DMultisampleIMG(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_TEXTURE_2D, (GLuint) cb->id, 0, cb->getSamples());
    #else
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_TEXTURE_2D_MULTISAMPLE, (GLuint) cb->id, 0);
    #endif
}

void FrameBuffer::setDepthBuffer(Multisampler2D *db) {
    ismultisampled = true;
    use();
    if (db != (Multisampler2D*) 1) {
        this->db = (Sampler2D*) db;
        width = db->getWidth();
        height = db->getHeight();
        #ifdef OPENGLES
        glFramebufferTexture2DMultisampleIMG(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, (GLuint) db->id, 0, db->getSamples());
        #else
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D_MULTISAMPLE, (GLuint) db->id, 0);
        #endif
    } else {
        /*
        GLuint id;
        glGenRenderbuffers(1, &id);
        glBindRenderbuffer(GL_RENDERBUFFER, id);
        glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_DEPTH_COMPONENT16, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, id);
        this->db = (Sampler2D*) id;
        dbInternal = true;
        */
    }
}

void FrameBuffer::setStencilBuffer(Multisampler2D *sb) {
    ismultisampled = true;
    use();
    if (sb != (Multisampler2D*) 1) {
        this->sb = (Sampler2D*) sb;
        width = sb->getWidth();
        height = sb->getHeight();
        #ifdef OPENGLES
        glFramebufferTexture2DMultisampleIMG(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, (GLuint) sb->id, 0, sb->getSamples());
        #else
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D_MULTISAMPLE, (GLuint) sb->id, 0);
        #endif
    } else {
        /*
        GLuint id;
        glGenRenderbuffers(1, &id);
        glBindRenderbuffer(GL_RENDERBUFFER, id);
        glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_STENCIL_INDEX8, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, id, 0);
        this->sb = (Sampler2D*) id;
        sbInternal = true;
        */
    }

}

void FrameBuffer::setColorBuffer(Sampler2D *cb, uint8 index) {
    use();
    this->cb = (Sampler2D*) cb;
    width = cb->getWidth();
    height = cb->getHeight();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_TEXTURE_2D, (GLuint) cb->id, 0);
}

void FrameBuffer::setDepthBuffer(Sampler2D *db) {
    use();
    if (db != (Sampler2D*) 1) {
        this->db = (Sampler2D*) db;
        width = db->getWidth();
        height = db->getHeight();
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, (GLuint) db->id, 0);
    } else {
        GLuint id;
        glGenRenderbuffers(1, &id);
        glBindRenderbuffer(GL_RENDERBUFFER, id);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, id);
        this->db = (Sampler2D*) id;
        dbInternal = true;
    }
}

void FrameBuffer::setStencilBuffer(Sampler2D *sb) {
    use();
    if (sb != (Sampler2D*) 1) {
        this->sb = (Sampler2D*) sb;
        width = sb->getWidth();
        height = sb->getHeight();
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, (GLuint) sb->id, 0);
    } else {
        GLuint id;
        glGenRenderbuffers(1, &id);
        glBindRenderbuffer(GL_RENDERBUFFER, id);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_STENCIL_INDEX8, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, id, 0);
        this->sb = (Sampler2D*) id;
        sbInternal = true;
    }
}

void FrameBuffer::setColorBuffer(Sampler3D *cb, uint32 layer) {
    use();
    width = cb->getWidth();
    height = cb->getHeight();
    glFramebufferTexture3D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_3D, (GLuint) cb->id, 0, layer);
}

void FrameBuffer::setColorBuffer(SamplerCube *cb, uint32 side, uint8 index) {
    use();
    width = height = cb->getDimension();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, side, (GLuint) cb->id, 0);
}

#ifdef ANDROID
#include <android/log.h>
#endif

void FrameBuffer::draw(FrameBuffer *source, int32 x, int32 y) { draw(source, x, y, source->getWidth(), source->getHeight()); }
void FrameBuffer::draw(FrameBuffer *source, int32 x, int32 y, uint32 w, uint32 h) {
    RenderProgram *cp = Context::getCurrent()->copyProgram;
    UniformBuffer *ub = cp->getLocalUniformBuffer();

    vec2 resolution = vec2(getWidth(), getHeight());
    vec2 dimension = vec2(w, h) / resolution;
    vec2 position = vec2(x, y) / resolution * 2.0 - (vec2(1.0) - dimension);
    position.y = -position.y;

    ub->uniform2("position", (float32*) &position);
    ub->uniform2("dimension", (float32*) &dimension);
    cp->sampler("source", source->getColorBuffer(0));
    cp->render(this, RenderProgram::TRIANGLES, Context::getCurrent()->getQuad());
}

/* Code still usable for MSAA resolving. Remember that the x,y coordinates are Y up instead of Y down
void FrameBuffer::draw(FrameBuffer *source, int32 x, int32 y) {
    int32 width = source->getWidth();
    int32 height = source->getHeight();
    int32 maxWidth = getWidth() - x;
    int32 maxHeight = getHeight() - y;
    if (width >= maxWidth) width = maxWidth;
    if (height >= maxHeight) height = maxHeight;
    #ifdef OPENGLES
    RenderProgram *cp = Context::getCurrent()->copyProgram;
    float32 dstDimension[2]; dstDimension[0] = getWidth(); dstDimension[1] = getHeight();
    float32 srcDimension[2]; srcDimension[0] = source->getWidth(); srcDimension[1] = source->getHeight();
    float32 position[2]; position[0] = x; position[1] = y;
    __android_log_print(ANDROID_LOG_INFO, "ERROR", "dstDimension %fx%f", dstDimension[0], dstDimension[1]);
    __android_log_print(ANDROID_LOG_INFO, "ERROR", "srcDimension %fx%f", srcDimension[0], srcDimension[1]);
    __android_log_print(ANDROID_LOG_INFO, "ERROR", "position %fx%f", position[0], position[1]);
    cp->getLocalUniformBuffer()->uniform2("position", position);
    cp->getLocalUniformBuffer()->uniform2("dstDimension", dstDimension);
    cp->getLocalUniformBuffer()->uniform2("srcDimension", srcDimension);
    cp->sampler("source", source->getColorBuffer(0));
    cp->render(this, RenderProgram::TRIANGLES, Context::getCurrent()->getQuad());
    #else
    glBindFramebuffer(GL_READ_FRAMEBUFFER, (GLuint) source->id);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, (GLuint) id);
    glBlitFramebuffer(0, 0, width, height, x, y, x + width, y + height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    Context::getCurrent()->boundFrameBuffer = 0;
    #endif
}
*/

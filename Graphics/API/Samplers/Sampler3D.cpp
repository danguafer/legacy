#include "Sampler3D.h"

#include "../Context.h"

#include "../third-party/glLoader/glLoader.h"

using namespace Silexars::Graphics::API;
using namespace Samplers;

Sampler3D::Sampler3D(uint32 w, uint32 h, uint32 d, FORMAT format, void *data) : Sampler(format) {
    width = w;
    height = h;
    depth = d;

    use(0);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
#ifdef DESKTOP
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);
#endif

    glTexImage3D(GL_TEXTURE_3D, 0, internalFormat, w, h, d, 0, dataFormat, GL_UNSIGNED_BYTE, data);
}

void Sampler3D::use(uint8 unit) { bind(unit, GL_TEXTURE_3D); }

uint32 Sampler3D::getWidth() const { return width; }
uint32 Sampler3D::getHeight() const { return height; }
uint32 Sampler3D::getDepth() const { return depth; }

bool Sampler3D::read(void *data) {
    Context::current->pixelReadFrameBuffer->use();
    for (uint32 i = 0; i < depth; i++) {
        Context::current->pixelReadFrameBuffer->setColorBuffer(this, i);
        glReadPixels(0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, ((uint8*)data)+(width*height*i));
    }
    return true;
}

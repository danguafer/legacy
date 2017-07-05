#include "Sampler1D.h"
#include "../Context.h"

#include "../third-party/glLoader/glLoader.h"

using namespace Silexars::Graphics::API;
using namespace Samplers;

Sampler1D::Sampler1D(uint32 w, FORMAT format, void *data) : Sampler(format) {
    width = w;

    use(0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, w, 1, 0, dataFormat, GL_UNSIGNED_BYTE, data);
}

void Sampler1D::use(uint8 unit) { bind(unit, GL_TEXTURE_2D); }

uint32 Sampler1D::getWidth() const { return width; }

bool Sampler1D::read(void *data) {
    Context::current->pixelReadFrameBuffer->setColorBuffer(this);
    Context::current->pixelReadFrameBuffer->use();
    glReadPixels(0, 0, width, 1, dataFormat, GL_UNSIGNED_BYTE, data);
    return true;
}

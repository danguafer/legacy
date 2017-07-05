#include "Sampler2D.h"
#include "../Context.h"

#include "../third-party/glLoader/glLoader.h"

using namespace Silexars::Graphics::API;
using namespace Samplers;
using namespace Buffers;

Sampler2D::Sampler2D(uint32 w, uint32 h, FORMAT format, void *data) : Sampler(format) {
    width = w;
    height = h;

    use(0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, w, h, 0, dataFormat, GL_UNSIGNED_BYTE, data);
}

void Sampler2D::use(uint8 unit) { bind(unit, GL_TEXTURE_2D); }

uint32 Sampler2D::getWidth() const { return width; }
uint32 Sampler2D::getHeight() const { return height; }

void Sampler2D::write(void *data) {
    use(0);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);
}

bool Sampler2D::read(void *data) {
    Context::current->pixelReadFrameBuffer->setColorBuffer(this);
    Context::current->pixelReadFrameBuffer->use();
    glReadPixels(0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);
    return true;
}

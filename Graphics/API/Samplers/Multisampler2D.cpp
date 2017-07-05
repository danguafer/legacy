#include "Multisampler2D.h"
#include "../Context.h"

#include "../third-party/glLoader/glLoader.h"

using namespace Silexars::Graphics::API;
using namespace Samplers;
using namespace Buffers;

Multisampler2D::Multisampler2D(uint32 w, uint32 h, FORMAT format, uint8 samples) : Sampler(format) {
    width = w;
    height = h;
    this->samples = samples;

    use(0);
    #ifdef OPENGLES
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, w, h, 0, dataFormat, GL_UNSIGNED_BYTE, 0);
    #else
    glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, internalFormat, w, h, false);
    #endif
}

void Multisampler2D::use(uint8 unit) {
    #ifdef OPENGLES
    bind(unit, GL_TEXTURE_2D);
    #else
    bind(unit, GL_TEXTURE_2D_MULTISAMPLE);
    #endif
}

uint32 Multisampler2D::getWidth() const { return width; }
uint32 Multisampler2D::getHeight() const { return height; }
uint8 Multisampler2D::getSamples() const { return samples; }

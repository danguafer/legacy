#include "Sampler.h"
#include "../Context.h"
#include "../third-party/glLoader/glLoader.h"

using namespace Silexars::Graphics::API;
using namespace Samplers;

Sampler::Sampler(uint32 format) {
    glGenTextures(1, (GLuint*) &id);

    internalFormat = GL_RGBA;
    dataFormat = format;
    if (format == ALPHA || format == LUMINANCE || format == LUMINANCE_ALPHA || format == RGB) {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glPixelStorei(GL_PACK_ALIGNMENT, 1);
    }
}

Sampler::~Sampler() { glDeleteTextures(1, (GLuint*) &id); }

void Sampler::unit(uint8 unit) {
    if (Context::current->boundSamplerUnit != unit) {
        Context::current->boundSamplerUnit  = unit;
        glActiveTexture(GL_TEXTURE0 + unit);
    }
}

#warning Deactivated because of bug on (Shared/Canvas fillcolor bug testcase/code.cpp)
void Sampler::bind(uint8 punit, uint32 target) {
//    if (Context::current->boundSampler[punit] != this) {
        Context::current->boundSampler[punit]  = this;

        unit(punit);
        glBindTexture(target, (GLuint) id);
//    }
}

void Sampler::bindImage(uint8 unit, uint32 permission) {
    if (Context::current->boundImage[unit] != this) {
        Context::current->boundImage[unit]  = this;
        //glBindImageTexture(unit, (GLuint) id, 0, GL_FALSE, 0, permission, internalFormat);
    }
}

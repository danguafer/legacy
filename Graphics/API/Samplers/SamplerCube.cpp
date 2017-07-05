#include "SamplerCube.h"
#include "../Context.h"

#include "../third-party/glLoader/glLoader.h"

using namespace Silexars::Graphics::API::Samplers;

SamplerCube::SamplerCube(uint32 dimension, FORMAT format, void *sidesData) : Sampler(format) {
    uint8* data = (uint8*) sidesData;
    uint8 channels;
    switch (dataFormat) {
        case ALPHA: case LUMINANCE: channels = 1; break;
        case LUMINANCE_ALPHA: channels = 2; break;
        case RGB: channels = 3; break;
        case RGBA: channels = 4; break;
    }

    void *nx, *px, *ny, *py, *nz, *pz;
    if (sidesData) {
        nx = data; data += dimension*dimension*channels;
        px = data; data += dimension*dimension*channels;
        ny = data; data += dimension*dimension*channels;
        py = data; data += dimension*dimension*channels;
        nz = data; data += dimension*dimension*channels;
        pz = data;
    } else nx = px = ny = py = nz = pz = 0;
    CSamplerCube(dimension, format, nx, px, ny, py, nz, pz);
}

SamplerCube::SamplerCube(uint32 dimension, FORMAT format, void *nx, void *px, void *ny, void *py, void *nz, void *pz) : Sampler(format) {
    CSamplerCube(dimension, format, nx, px, ny, py, nz, pz);
}

void SamplerCube::CSamplerCube(uint32 dimension, FORMAT format, void *nx, void *px, void *ny, void *py, void *nz, void *pz) {
    this->dimension = dimension;

    use(0);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
#ifdef DESKTOP
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
#endif

    void* data[] = { px, nx, py, ny, pz, nz };
    for (uint32 i = 0; i < 6; i++) glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, internalFormat, dimension, dimension, 0, dataFormat, GL_UNSIGNED_BYTE, data[i]);
}

void SamplerCube::use(uint8 unit) { bind(unit, GL_TEXTURE_CUBE_MAP); }

uint32 SamplerCube::getDimension() const { return dimension; }

bool SamplerCube::read(void *sidesData) {
    uint8* data = (uint8*) sidesData;

    uint8 channels;
    switch (dataFormat) {
        case ALPHA: case LUMINANCE: channels = 1; break;
        case LUMINANCE_ALPHA: channels = 2; break;
        case RGB: channels = 3; break;
        case RGBA: channels = 4; break;
    }

    void *nx = data; data += dimension*dimension*channels;
    void *px = data; data += dimension*dimension*channels;
    void *ny = data; data += dimension*dimension*channels;
    void *py = data; data += dimension*dimension*channels;
    void *nz = data; data += dimension*dimension*channels;
    void *pz = data;
    return read(nx, px, ny, py, nz, pz);
}

bool SamplerCube::read(void *nx, void *px, void *ny, void *py, void *nz, void *pz) {
    uint32 sides[] = { GL_TEXTURE_CUBE_MAP_NEGATIVE_X, GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, GL_TEXTURE_CUBE_MAP_POSITIVE_Z };
    void* buffers[] = { nx, px, ny, py, nz, pz };

    Context::current->pixelReadFrameBuffer->use();
    for (uint32 i = 0; i < 6; i++) {
        if (buffers[i]) {
            Context::current->pixelReadFrameBuffer->setColorBuffer(this, sides[i]);
            glReadPixels(0, 0, dimension, dimension, dataFormat, GL_UNSIGNED_BYTE, buffers[i]);
        }
    }
    return true;
}

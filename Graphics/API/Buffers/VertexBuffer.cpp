#include "VertexBuffer.h"
#include "../third-party/glLoader/glLoader.h"
#include "../Context.h"

using namespace Silexars::Graphics::API::Buffers;

VertexBuffer::VertexBuffer(uint32 components, uint32 quantity, uint32 format, void* data) {
    this->components = components;
    this->quantity = quantity;
    this->format = format;

    uint32 size = quantity*components;

    switch (format) {
        case INT16: case UINT16:               size *= 2; break;
        case INT32: case UINT32: case FLOAT32: size *= 4; break;
        case FLOAT64:                          size *= 8; break;
    }

    use();
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

#include <iostream>

void VertexBuffer::use() {
    if (Context::current->boundVertexBuffer != this) {
        Context::current->boundVertexBuffer  = this;
        glBindBuffer(GL_ARRAY_BUFFER, (GLuint) id);
    }
}

uint32 VertexBuffer::getQuantity() const { return quantity; }
uint32 VertexBuffer::getComponents() const { return components; }

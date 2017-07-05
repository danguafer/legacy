#include "IndexBuffer.h"
#include "../third-party/glLoader/glLoader.h"
#include "../Context.h"

using namespace Silexars::Graphics::API::Buffers;

#include <iostream>

IndexBuffer::IndexBuffer(uint32 quantity, uint32 format, void* data) {
    this->quantity = quantity;
    this->format = format;
    uint32 size = quantity;

    if (format == UINT16) size *= 2;

    use();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

uint32 IndexBuffer::getQuantity() const { return quantity; }

void IndexBuffer::use() {
    if (Context::current->boundIndexBuffer != this) {
        Context::current->boundIndexBuffer  = this;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (GLuint) id);
    }
}

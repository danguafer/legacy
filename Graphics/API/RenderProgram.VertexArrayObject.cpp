#include "RenderProgram.VertexArrayObject.h"

#include "third-party/glLoader/glLoader.h"

#include <cstdlib>

using namespace Silexars::Graphics::API;
using namespace Buffers;

RenderProgram::VertexArrayObject::VertexArrayObject() {
    nlocations = 0;
    locations = 0;
    vbs = 0;
    ib = 0;
}

RenderProgram::VertexArrayObject::~VertexArrayObject() {
    free(locations);
    free(vbs);
}

void RenderProgram::VertexArrayObject::setVertexBuffer(uint32 location, VertexBuffer *vb) {
    for (uint32 i = 0; i < nlocations; i++)
        if (locations[i] == location) {
            if (vb) vbs[i] = vb;
            else {
                locations[i] = locations[nlocations - 1];
                vbs[i] = vbs[nlocations - 1];
                nlocations--;
            }
            return;
        }

    if (vb) {
        nlocations++;
        locations = (uint32*) realloc(locations, nlocations*sizeof(uint32));
        vbs = (VertexBuffer**) realloc(vbs, nlocations*sizeof(VertexBuffer*));

        locations[nlocations - 1] = location;
        vbs[nlocations - 1] = vb;

        glEnableVertexAttribArray(location);
    }
}

VertexBuffer* RenderProgram::VertexArrayObject::getVertexBuffer(uint32 location) const {
    for (uint32 i = 0; i < nlocations; i++)
        if (locations[i] == location) return vbs[i];
    return 0;
}

void RenderProgram::VertexArrayObject::setIndexBuffer(IndexBuffer *ib) { this->ib = ib; }
IndexBuffer* RenderProgram::VertexArrayObject::getIndexBuffer() const { return ib; }

void RenderProgram::VertexArrayObject::use() {
    for (uint32 i = 0; i < nlocations; i++) {
        VertexBuffer *vb = vbs[i];
        vb->use();
        glVertexAttribPointer(locations[i], vb->getComponents(), vb->format, 0, 0, 0);
    }

    if (ib) ib->use();
}

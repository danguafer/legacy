#ifndef SILEXARS_GRAPHICS_API_BUFFERS_VERTEXBUFFER_H
#define SILEXARS_GRAPHICS_API_BUFFERS_VERTEXBUFFER_H

#include "Buffer.h"

namespace Silexars {
    namespace Graphics {
        namespace API {
            class RenderProgram;
            namespace Buffers {
                class VertexBuffer : public Buffer {
                    public:
                        VertexBuffer(uint32 components, uint32 quantity, uint32 format, void *data);

                        uint32 getComponents() const;
                        uint32 getQuantity() const;

                        enum FORMAT { INT8 = 0x1400, UINT8 = 0x1401, INT16 = 0x1402, UINT16 = 0x1403, INT32 = 0x1404, UINT32 = 0x1405, FLOAT32 = 0x1406, FLOAT64 = 0x140A };
                    private:
                        friend class API::RenderProgram;

                        void use();

                        uint32 components, format, quantity;
                };
            }
        }
    }
}

#endif // VERTEXBUFFER_H

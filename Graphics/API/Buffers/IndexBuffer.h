#pragma once

#include "Buffer.h"

namespace Silexars {
    namespace Graphics {
        namespace API {
            class RenderProgram;
            namespace Buffers {
                class IndexBuffer : public Buffer {
                    public:
                        IndexBuffer(uint32 quantity, uint32 format, void* data);

                        uint32 getQuantity() const;

                        enum FORMAT { UINT8 = 0x1401, UINT16 = 0x1403 /*, UINT32 = 0x1405 GLES 2.0 doesn't support it */ };
                    private:
                        friend class API::RenderProgram;

                        void use();

                        uint32 format, quantity;
                };
            }
        }
    }
}

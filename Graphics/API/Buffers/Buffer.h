#pragma once

#include <Veritas/Definitions/Definitions.h>

namespace Silexars {
    namespace Graphics {
        namespace API {
            namespace Buffers {
                class Buffer {
                    protected:
                        Buffer();
                        ~Buffer();

                        Handle id;
                };
            }
        }
    }
}

//! Only supports 8 textures

#pragma once

#include <Veritas/Definitions/Definitions.h>

namespace Silexars {
    namespace Graphics {
        namespace API {
            class Program;
            class RenderProgram;
            class ComputeProgram;
            namespace Buffers {
                class FrameBuffer;
            }
            namespace Samplers {
                class Sampler {
                    public:
                        ~Sampler();

                        enum FORMAT { ALPHA = 0x1906, LUMINANCE = 0x1909, LUMINANCE_ALPHA = 0x190A, RGB = 0x1907, RGBA = 0x1908};
                    protected:
                        friend class Buffers::FrameBuffer;
                        friend class API::Program;
                        friend class API::RenderProgram;
                        friend class API::ComputeProgram;

                        uint32 internalFormat;
                        uint32 dataFormat;

                        Sampler(uint32 format);
                        virtual void use(uint8 unit) = 0;

                        void unit(uint8 unit);
                        void bind(uint8 unit, uint32 target);
                        void bindImage(uint8 unit, uint32 permission);

                        Handle id;
                };
            }
        }
    }
}

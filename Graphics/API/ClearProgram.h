#pragma once

#include <Veritas/Math/Math.h>
#include "Program.h"

namespace Silexars {
    namespace Graphics {
        namespace API {
            class ClearProgram {
                public:
                    ClearProgram();
                    ~ClearProgram();

                    void clear(Silexars::Graphics::API::Buffers::FrameBuffer *fb, uint32 bufferBits = COLOR_BUFFER_BIT | DEPTH_BUFFER_BIT | STENCIL_BUFFER_BIT);
                    enum BUFFER_BITS { COLOR_BUFFER_BIT = 0x00004000, DEPTH_BUFFER_BIT = 0x00000100, STENCIL_BUFFER_BIT = 0x00000400 };

                    void setColor(Math::vec4 color);
                    Math::vec4 getColor() const;

                    void setDepth(float32 depth);
                    float32 getDepth() const;

                    void setStencil(int32 stencil);
                    int32 getStencil() const;
                private:
                    Math::vec4 color;
                    float32 depth;
                    int32 stencil;
                    bool iscolorblending;

                    friend class Context;
                    class GPU {
                        public:
                            GPU();
                            void setColor(Math::vec4 color);
                            void setDepth(float32 depth);
                            void setStencil(int32 stencil);
                        private:
                            Math::vec4 color;
                            float32 depth;
                            int32 stencil;
                    };
            };
        }
    }
}

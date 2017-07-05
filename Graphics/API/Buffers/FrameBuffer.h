#pragma once

#include <Veritas/Definitions/Definitions.h>

#include "../Samplers/Samplers.h"

#include "ColorBuffer.h"
#include "DepthBuffer.h"
#include "StencilBuffer.h"

#include <Veritas/Math/Math.h>

namespace Silexars {
    namespace Graphics {
        namespace API {
            class Context;
            class RenderProgram;
            class ClearProgram;
            namespace Buffers {
                class FrameBuffer {
                    public:
                        FrameBuffer();
                        FrameBuffer(Samplers::Sampler2D* cb, Samplers::Sampler2D* db, Samplers::Sampler2D* sb);
                        FrameBuffer(Samplers::Multisampler2D* cb, Samplers::Multisampler2D* db, Samplers::Multisampler2D* sb);
                        ~FrameBuffer();

                        bool isMultisampled() const;

                        void draw(FrameBuffer* source, int32 x = 0, int32 y = 0);
                        void draw(FrameBuffer *source, int32 x, int32 y, uint32 w, uint32 h);

                        void setColorBuffer(Samplers::SamplerCube *cb, uint32 side, uint8 index = 0);
                        void setDepthBuffer(Samplers::SamplerCube* db, uint32 side);
                        void setStencilBuffer(Samplers::SamplerCube *sb, uint32 side);

                        void setColorBuffer(Samplers::Sampler2D* cb, uint8 index = 0);
                        void setDepthBuffer(Samplers::Sampler2D* db);
                        void setStencilBuffer(Samplers::Sampler2D *sb);

                        Samplers::Sampler2D* getColorBuffer(uint8 index = 0) const;
                        Samplers::Sampler2D* getDepthBuffer() const;
                        Samplers::Sampler2D* getStencilBuffer() const;

                        Math::vec2 getDimension() const;
                        uint32 getWidth();
                        uint32 getHeight();

                        static const Samplers::Sampler2D* INTERNAL;
                    private:
                        FrameBuffer(uint32 width, uint32 height);
                        friend class API::Context;
                        friend class API::RenderProgram;
                        friend class API::ClearProgram;
                        friend class Samplers::Sampler1D;
                        friend class Samplers::Sampler2D;
                        friend class Samplers::Sampler3D;
                        friend class Samplers::SamplerCube;

                        void setColorBuffer(Samplers::Multisampler2D* cb, uint8 index = 0);
                        void setDepthBuffer(Samplers::Multisampler2D* db);
                        void setStencilBuffer(Samplers::Multisampler2D* sb);

                        void setColorBuffer(Samplers::Sampler1D* cb);
                        void setDepthBuffer(Samplers::Sampler1D* db);
                        void setStencilBuffer(Samplers::Sampler1D *sb);

                        void setColorBuffer(Samplers::Sampler3D* cb, uint32 layer);
                        void setDepthBuffer(Samplers::Sampler3D* db, uint32 layer);
                        void setStencilBuffer(Samplers::Sampler3D *sb, uint32 layer);

                        uint32 width, height;

                        void use();

                        bool ismultisampled;
                        Handle id;
                        Samplers::Sampler2D *cb, *db, *sb;
                        bool dbInternal, sbInternal;
                };
            }
        }
    }
}

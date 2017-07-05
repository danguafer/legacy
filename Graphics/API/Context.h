#pragma once

#include "Program.h"
#include "RenderProgram.h"
#include "ClearProgram.h"
#include "Samplers/Samplers.h"
#include "Buffers/Buffers.h"

namespace Silexars {
    namespace Graphics {
        namespace API {
            class Context {
                public:
                    Context(void (*makeCurrent)(void *data), void (*swapBuffers)(void *data), void *data);
                    ~Context();

                    void makeCurrent();
                    void swapBuffers(Buffers::FrameBuffer *fb, int32 x = 0, int32 y = 0);
                    void swapBuffers(Buffers::FrameBuffer *fb, int32 x, int32 y, uint32 w, uint32 h);

                    RenderProgram::VertexArrayObject* getQuad();
                    RenderProgram::VertexArrayObject* getCube();
                    RenderProgram::VertexArrayObject* getSphere();

                    ClearProgram* getClearProgram() const;

                    static Context* getCurrent();
                private:
                    Buffers::FrameBuffer* getDefaultFrameBuffer() const;

                    void *data;
                    void (*fmakeCurrent)(void *data);
                    void (*fswapBuffers)(void *data);

                    uint32 viewportWidth, viewportHeight;

                    static Context* current;

                    ClearProgram* clearProgram;

                    Buffers::FrameBuffer* defaultFrameBuffer;

                    friend class Samplers::Sampler1D;
                    friend class Samplers::Sampler2D;
                    friend class Samplers::Sampler3D;
                    friend class Samplers::SamplerCube;
                    Buffers::FrameBuffer *pixelReadFrameBuffer;

                    friend class ClearProgram; ClearProgram::GPU GPUClearProgram;
                    friend class Program; Program* boundProgram;

                    friend class Buffers::FrameBuffer; Buffers::FrameBuffer* boundFrameBuffer;
                    friend class Buffers::IndexBuffer; Buffers::IndexBuffer* boundIndexBuffer;
                    friend class Buffers::VertexBuffer; Buffers::VertexBuffer* boundVertexBuffer;

                    friend class RenderProgram; RenderProgram::GPU GPURenderProgram;

                    uint8 boundSamplerUnit;
                    friend class Samplers::Sampler; Samplers::Sampler *boundSampler[8],*boundImage[8];

                    bool isMultisampling;

                    RenderProgram::VertexArrayObject *quad, *cube, *sphere;

                    RenderProgram *copyProgram;
            };
        }
    }
}

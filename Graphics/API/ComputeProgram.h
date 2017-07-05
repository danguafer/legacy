#pragma once

#include "Program.h"
#include "Shaders/Shaders.h"
#include "Buffers/Buffers.h"
#include "Samplers/Samplers.h"

namespace Silexars {
    namespace Graphics {
        namespace API {
            class ComputeProgram : public Program {
                public:
                    ComputeProgram(Shaders::ComputeShader *cs);

                    Shaders::ComputeShader *getComputeShader() const;

                    void sampler(int32 uniform, Samplers::Sampler *sampler, uint8 permission);
                    void sampler(const char* uniform, Samplers::Sampler *sampler, uint8 permission);
                    enum PERMISSION { READ_ONLY = 0x88B8, WRITE_ONLY = 0x88B9, READ_WRITE = 0x88BA };

                    void compute(uint32 w, uint32 h, uint32 d);
                private:
                    Shaders::ComputeShader *cs;
            };
        }
    }
}

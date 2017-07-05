#pragma once

#include "Sampler.h"

namespace Silexars {
    namespace Graphics {
        namespace API {
            namespace Samplers {
                class SamplerCube : public Sampler {
                    public:
                        SamplerCube(uint32 dimension, FORMAT format, void *sidesData = 0);
                        SamplerCube(uint32 dimension, FORMAT format, void *nx, void *px, void *ny, void *py, void *nz, void *pz);

                        uint32 getDimension() const;

                        bool read(void *sidesData);
                        bool read(void *nx, void *px, void *ny, void *py, void *nz, void *pz);

                        enum FACES { POSITIVE_X = 0x8515, NEGATIVE_X, POSITIVE_Y, NEGATIVE_Y, POSITIVE_Z, NEGATIVE_Z };
                    private:
                        uint32 dimension;

                        void CSamplerCube(uint32 dimension, FORMAT format, void *nx, void *px, void *ny, void *py, void *nz, void *pz);

                        void use(uint8 unit);
                };
            }
        }
    }
}

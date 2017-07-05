#pragma once

#include "Sampler.h"

namespace Silexars {
    namespace Graphics {
        namespace API {
            namespace Samplers {
                class Sampler1D : public Sampler {
                    public:
                        Sampler1D(uint32 w, FORMAT format, void *data = 0);

                        uint32 getWidth() const;

                        bool read(void *data);
                    private:
                        void use(uint8 unit);

                        uint32 width;
                };
            }
        }
    }
}

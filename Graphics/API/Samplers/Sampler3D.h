#pragma once

#include "Sampler.h"

namespace Silexars {
    namespace Graphics {
        namespace API {
            namespace Samplers {
                class Sampler3D : public Sampler {
                    public:
                        Sampler3D(uint32 w, uint32 h, uint32 d, FORMAT channels, void *data = 0);

                        uint32 getWidth() const;
                        uint32 getHeight() const;
                        uint32 getDepth() const;

                        bool read(void *data);
                    private:
                        void use(uint8 unit);

                        uint32 width,height,depth;
                };
            }
        }
    }
}

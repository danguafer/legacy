#pragma once

#include "Sampler.h"
#include "Sampler1D.h"
#include "Sampler3D.h"

#warning MULTISAMPLING: Remove all interfaces from other methods and create an interface that creates and/or process a Sampler2D.

namespace Silexars {
    namespace Graphics {
        namespace API {
            namespace Samplers {
                class Multisampler2D : public Sampler {
                    public:
                        Multisampler2D(uint32 w, uint32 h, FORMAT channels, uint8 samples);

                        uint32 getWidth() const;
                        uint32 getHeight() const;
                        uint8 getSamples() const;
                    private:
                        void use(uint8 unit);

                        uint32 width, height;
                        uint8 samples;
                };
            }
        }
    }
}

#pragma once

#include "Sampler.h"
#include "Sampler1D.h"
#include "Sampler3D.h"
#include "Multisampler2D.h"

#warning IMPLEMENT MULTISAMPLING INTERFACES

namespace Silexars {
    namespace Graphics {
        namespace API {
            namespace Samplers {
                class Sampler2D : public Sampler {
                    public:
                        Sampler2D(uint32 w, uint32 h, FORMAT channels, void *data = 0);
                        Sampler2D(Multisampler2D *ms);

                        uint32 getWidth() const;
                        uint32 getHeight() const;

                        void write(void *data);
                        void write(Multisampler2D *ms);
                        bool read(void *data);
                    private:
                        void use(uint8 unit);

                        uint32 width, height;
                };
            }
        }
    }
}

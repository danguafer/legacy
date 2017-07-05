#pragma once

#include "Object.h"

#include <Veritas/Graphics/API/API.h>

namespace Silexars {
    namespace AEngine {
        namespace Cinema {
            class Object::Material {
                public:
                    Material(Graphics::API::Samplers::Sampler2D* albedo);

                    Graphics::API::Samplers::Sampler2D* getAlbedo() const;
                private:
                    Graphics::API::Samplers::Sampler2D* albedo;
            };
        }
    }
}

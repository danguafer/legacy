#pragma once

#include <Veritas/Silexars.h>

#include "CinemaObject.h"

namespace Silexars {
    namespace AEngine {
        namespace Renderers {
            class GraphicsRenderer;
        }

        namespace Cinema {

            class Object : public CinemaObject {
                public:
                    class Material;

                    Object(Material *material, Graphics::API::RenderProgram::VertexArrayObject *vao);
                    ~Object();

                    Graphics::API::RenderProgram::VertexArrayObject* getVAO() const;

                    Material* getMaterial() const;

                    uint8 getType() const;
                private:
                    friend class Renderers::GraphicsRenderer;

                    Material *material;

                    Graphics::API::RenderProgram::VertexArrayObject *vao;
            };
        }
    }
}

#include "Object.Material.h"

#pragma once

#include <Veritas/Silexars.h>
#include "CinemaObject.h"
#include "Object.h"

namespace Silexars {
    namespace AEngine {
        namespace Renderers { class GraphicsRenderer; }
        namespace Cinema {
            class Scene;
            class Camera : public CinemaObject {
                public:
                    Camera();
                    virtual ~Camera();

                    uint8 getType() const;

                    virtual void clear() = 0;
                    virtual void render(Scene *scene) = 0;
                    virtual void display() = 0;
                    virtual uint8 getCameraType() const = 0;

                    enum TYPE { MONO, STEREO, CUBE };

                    class Mono;
                    class Stereo;
                    class Cube;
                protected:
                    friend class Renderers::GraphicsRenderer;

                    Math::mat4 projection;
                    Graphics::API::Buffers::UniformBuffer* ubo;

                    virtual void render(Graphics::API::RenderProgram *rp, Object *object) = 0;
                    virtual void render(Graphics::API::RenderProgram *rp, Graphics::API::Samplers::SamplerCube *skybox) = 0;
            };
        }
    }
}

#include "Camera.Mono.h"
#include "Camera.Stereo.h"
#include "Camera.Cube.h"

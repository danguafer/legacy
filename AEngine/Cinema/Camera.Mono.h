#ifndef SILEXARS_AENGINE_CINEMA_CAMERA_MONO_H
#define SILEXARS_AENGINE_CINEMA_CAMERA_MONO_H

#include "Camera.h"

namespace Silexars {
    namespace AEngine {
        namespace Cinema {
            class Camera::Mono : public Camera {
                public:
                    Mono(uint32 width, uint32 height, float32 fov = 45.0f);
                    ~Mono();

                    void clear();
                    void render(Scene *scene);
                    void display(Graphics::API::Buffers::FrameBuffer *framebuffer);

                    Graphics::API::Samplers::Sampler2D* getSampler2D() const;

                    uint8 getCameraType() const;

                    uint32 getWidth() const;
                    uint32 getHeight() const;
                private:
                    friend class Renderers::GraphicsRenderer;
                    Graphics::API::Buffers::FrameBuffer *fb;

                    uint32 width, height;

                    void render(Graphics::API::RenderProgram *rp, Object *object);
                    void render(Graphics::API::RenderProgram *rp, Graphics::API::Samplers::SamplerCube *skybox);
            };
        }
    }
}

#endif // CAMERA_MONO_H

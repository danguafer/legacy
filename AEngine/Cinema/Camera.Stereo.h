#ifndef SILEXARS_AENGINE_CINEMA_CAMERA_STEREO_H
#define SILEXARS_AENGINE_CINEMA_CAMERA_STEREO_H

#include "Camera.h"

namespace Silexars {
    namespace AEngine {
        namespace Cinema {
            class Camera::Stereo : public Camera {
                public:
                    Stereo(uint32 width, uint32 height, float32 fov = 45.0f);
                    ~Stereo();

                    void clear();
                    void render(Scene *scene);
                    void display(Graphics::API::Buffers::FrameBuffer *framebuffer);

                    void setPupillaryDistance(float32 distance);
                    float32 getPupillaryDistance() const;

                    Graphics::API::Samplers::Sampler2D* getLeftSampler2D() const;
                    Graphics::API::Samplers::Sampler2D* getRightSampler2D() const;

                    uint8 getCameraType() const;

                    uint32 getWidth() const;
                    uint32 getHeight() const;
                private:
                    friend class Renderers::GraphicsRenderer;
                    Graphics::API::Buffers::FrameBuffer *left, *right;

                    uint32 width, height;
                    float32 pupillaryDistance;

                    void render(Graphics::API::RenderProgram *rp, Object *object);
                    void render(Graphics::API::RenderProgram *rp, Graphics::API::Samplers::SamplerCube *skybox);
            };
        }
    }
}

#endif // CAMERA_STEREO_H

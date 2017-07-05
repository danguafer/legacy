#ifndef SILEXARS_AENGINE_CINEMA_CAMERA_CUBE_H
#define SILEXARS_AENGINE_CINEMA_CAMERA_CUBE_H

#include "Camera.h"

namespace Silexars {
    namespace AEngine {
        namespace Cinema {
            class Camera::Cube : public Camera {
                public:
                    Cube(uint32 dimension);
                    ~Cube();

                    void clear();
                    void render(Scene *scene);
                    void display(Graphics::API::Buffers::FrameBuffer *framebuffer);

                    Graphics::API::Samplers::SamplerCube* getSamplerCube() const;

                    uint32 getDimension() const;

                    uint8 getCameraType() const;
                private:
                    friend class Renderers::GraphicsRenderer;

                    Graphics::API::Samplers::SamplerCube *cube;
                    Graphics::API::Buffers::FrameBuffer *nx, *px, *ny, *py, *nz, *pz;

                    void render(Graphics::API::RenderProgram *rp, Object *object);
                    void render(Graphics::API::RenderProgram *rp, Graphics::API::Samplers::SamplerCube *skybox);
            };
        }
    }
}

#endif // CAMERA_CUBE_H

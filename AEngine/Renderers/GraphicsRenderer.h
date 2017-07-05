#pragma once

#include <Veritas/Silexars.h>

#include "../Cinema/Cinema.h"

namespace Silexars {
    namespace AEngine {
        namespace Renderers {
            class GraphicsRenderer {
                public:
                    GraphicsRenderer(Silexars::System::UI::Window *window);
                    ~GraphicsRenderer();

                    enum LOCATIONS { VERTICES = 0, NORMALS = 1, TEXCOORDS = 2 };

                    class Level0;
                    class Level1;
                protected:
                    Graphics::API::Context *ctx;

                    virtual void render(Cinema::Camera *camera, Cinema::Scene* scene);
                    void render(Cinema::Camera *camera, Cinema::Scene *scene, Math::mat4 transformation);
                    virtual void render(Cinema::Camera *camera, Cinema::Object *object, Math::mat4 transformation) = 0;
                    virtual void render(Cinema::Camera *camera, Graphics::API::Samplers::SamplerCube *skybox) = 0;

                    friend class Cinema::Camera::Mono;
                    friend class Cinema::Camera::Stereo;
                    friend class Cinema::Camera::Cube;
                    Silexars::Graphics::API::RenderProgram *displayMono, *displayStereo, *displayCube;
                    void display(Cinema::Camera::Mono *camera, Graphics::API::Buffers::FrameBuffer *framebuffer);
                    void display(Cinema::Camera::Stereo *camera, Graphics::API::Buffers::FrameBuffer *framebuffer);
                    void display(Cinema::Camera::Cube *cube, Graphics::API::Buffers::FrameBuffer *framebuffer);
            };
        }
    }
}

#include "GraphicsRenderer.Level0.h"
#include "GraphicsRenderer.Level1.h"

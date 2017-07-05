#ifndef SILEXARS_AENGINE_RENDERERS_GRAPHICSRENDERER_LEVEL0_H
#define SILEXARS_AENGINE_RENDERERS_GRAPHICSRENDERER_LEVEL0_H

#include "GraphicsRenderer.h"

namespace Silexars {
    namespace AEngine {
        namespace Renderers {
            class GraphicsRenderer::Level0 : public GraphicsRenderer { // Base it on non-extended GLES 2.0
                public:
                    Level0(System::UI::Window *window);
                    ~Level0();                    

                private:
                    void render(Cinema::Camera *camera, Cinema::Scene* scene);
                    void render(Cinema::Camera *camera, Cinema::Object* object, Math::mat4 transformation);
                    void render(Cinema::Camera *camera, Graphics::API::Samplers::SamplerCube *skybox);

                    Graphics::API::RenderProgram *rp, *skyboxrp;
                    Graphics::API::Shaders::VertexShader *skeletonVS, *staticVS;
            };
        }
    }
}

#endif // GRAPHICSRENDERER_LEVEL0_H

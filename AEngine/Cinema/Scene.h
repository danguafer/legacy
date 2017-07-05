#pragma once

#include "CinemaObject.h"
#include <Veritas/Graphics/API/Samplers/SamplerCube.h>
#include <list>

namespace Silexars {
    namespace AEngine {
        namespace Renderers {
            class GraphicsRenderer;
        }

        namespace Cinema {
            class Scene : public CinemaObject {
                private:
                    typedef std::list<CinemaObject*> Container;
                public:
                    typedef Container::iterator iterator;

                    Scene();

                    uint8 getType() const;

                    void add(CinemaObject* object);
                    void remove(CinemaObject* object);

                    void setSkybox(Graphics::API::Samplers::SamplerCube *skybox);
                    Graphics::API::Samplers::SamplerCube* getSkybox() const;

                    iterator begin();
                    iterator end();
                    uint32 size();

                    static Scene* load(const char *path);
                private:
                    friend class AEngine::Renderers::GraphicsRenderer;

                    Graphics::API::Samplers::SamplerCube* skybox;
                    Container cObjs;
            };
        }
    }
}

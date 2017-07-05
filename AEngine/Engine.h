#pragma once

#include <Veritas/Silexars.h>

#include "Renderers/Renderers.h"
#include "Managers/ResourceManager.h"

namespace Silexars {
    namespace AEngine {
        class Engine : public System::Process, public Silexars::etc::StateMachine {
            public:
                Engine(const char *name);
                Engine(const char *name, uint32 width, uint32 height);
                ~Engine();

                Silexars::System::UI::Window* getWindow() const;

                Renderers::GraphicsRenderer* getGraphicsRenderer() const;

                static Engine* getCurrent();
            private:
                void CEngine();
                void run();

                Silexars::System::UI::Window w;

                Managers::ResourceManager *rManager;
                Renderers::GraphicsRenderer *grenderer;

                static Engine* current;

                class State0 : public Silexars::etc::StateMachine::State { public: void run(); };
                static State0 state0;
        };
    }
}

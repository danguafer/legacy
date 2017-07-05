#include "Engine.h"

using namespace Silexars;
using namespace AEngine;
using namespace Utils;

using namespace System::UI;

using namespace Renderers;
using namespace Managers;

Engine::State0 Engine::state0;
void Engine::State0::run() { /* empty state */ }

Engine* Engine::current = 0;
Engine* Engine::getCurrent() { return current; }

Engine::Engine(const char *name, uint32 width, uint32 height) : StateMachine(&state0), w(name, width, height) {
    CEngine();
}
Engine::Engine(const char *name) : StateMachine(&state0), w(name) {
    w.setFullscreen(true);
    CEngine();
}
void Engine::CEngine() {
    current = this;
    grenderer = new GraphicsRenderer::Level0(getWindow());
    rManager = new ResourceManager();
}
Engine::~Engine() {
    delete getState();
    delete grenderer;
    delete rManager;
}

void Engine::run() { StateMachine::run(); }
Window* Engine::getWindow() const { return (Window*) &w; }

GraphicsRenderer* Engine::getGraphicsRenderer() const { return grenderer; }

#ifndef SILEXARS_AENGINE_AENGINE_H_
#define SILEXARS_AENGINE_AENGINE_H_

#warning The Camera must take pictures! (Make it possible to get the Sampler back after rendering, it can also help lightning preprocessing on some GraphicsRenderer levels)
#warning The perspective projections must make it possible to configure the field of view

#warning Only for help to draft:
namespace Silexars {
    namespace AEngine {
        class Engine;
        namespace Cinema {
            class Scene;
            class Camera;
            class Light;
            class Audio;
            class Object;
        }
        namespace Renderers {
            class Renderer;
            class PhysicsRenderer;
            class AudioRenderer;
            class GraphicsRenderer;
        }
        namespace Controllers {
            class Controller;
            class Gamepad;
        }
    }
}

#include "Cinema/Cinema.h"
#include "Renderers/Renderers.h"
#include "Controllers/Controllers.h"
#include "Managers/Managers.h"
#include "Engine.h"

#endif

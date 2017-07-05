#pragma once

#include "../Cinema/Cinema.h"

namespace Silexars {
    namespace AEngine {
        namespace Controllers {
            class Controller {
                public:
                    Controller(Cinema::CinemaObject *object);
                    ~Controller();

                    void attach(Cinema::CinemaObject *object);

                    void control(uint32 dt);
                private:
                    Cinema::CinemaObject *object;
                    float32 rx, ry;
            };
        }
    }
}

//!Incomplete
#pragma once

#include "Touchscreen.h"
#include <Veritas/Math/vec2.h>

namespace Silexars {
    namespace System {
        namespace UI { class Window; }
        namespace IO {
            namespace Devices {
                class Touchscreen::Touch {
                    public:
                        bool isHovering() const;
                        Math::vec2 getInitialPosition() const;
                        Math::vec2 getPreviousPosition() const;
                        Math::vec2 getPosition() const;

                        uint8 getID() const;

                        uint32 getInitialTime() const;
                        uint32 getPreviousTime() const;
                        uint32 getTime() const;
                    protected:
                        friend class UI::Window;
                        Touch(Math::vec2 position, uint8 id, bool ishovering);
                        ~Touch();

                        void start(Math::vec2 position);
                        void move(Math::vec2 position);

                        Math::vec2 initialPosition, previousPosition, position;
                        uint32 initialTime, previousTime, time;
                        uint8 id;
                        bool ishovering;
                };
            }
        }
    }
}

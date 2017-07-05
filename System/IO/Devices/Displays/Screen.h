//!Complete

#ifndef SILEXARS_SYSTEM_DEVICES_DISPLAYS_H_
#define SILEXARS_SYSTEM_DEVICES_DISPLAYS_H_

#include "Display.h"

namespace Silexars {
    namespace System {
        namespace IO {
            namespace Devices {
                class GraphicsDevice;
                namespace Displays {
                    class Screen : public Display {
                        public:
                            uint8 getDeviceType() const;
                            const char* getName() const;

                            int32 getX() const;
                            int32 getY() const;
                            uint32 getWidth() const;
                            uint32 getHeight() const;

                            uint8 getIndex() const;
                        private:
                            friend class Devices::GraphicsDevice;
                            friend class UI::Window;
                            uint8 i;

                            GraphicsDevice *parent;

                            Screen(GraphicsDevice *display, uint8 i);
                            ~Screen();

                            void systemCreateScreen(GraphicsDevice *display, uint8 i);
                    };
                }
            }
        }
    }
}

#endif

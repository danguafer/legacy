//!Complete

#ifndef SILEXARS_MANAGEMENT_DEVICES_GRAPHICSDEVICE_H_
#define SILEXARS_MANAGEMENT_DEVICES_GRAPHICSDEVICE_H_

#include "Device.h"
#include <list>

#include "Displays/Displays.h"

namespace Silexars {
    namespace System {
        namespace Managers { namespace DeviceManagers { class GraphicsManager; } }
        namespace IO {
            namespace Devices {
                namespace Displays { class Screen; }
                class GraphicsDevice : public Device {
                    private:
                        typedef std::list<Displays::Screen*> List;
                    public:
                        typedef List::iterator iterator;

                        iterator begin();
                        iterator end();
                        uint32 size() const;

                        uint8 getDeviceType() const;

                        Displays::Screen* getDefaultScreen() const;

//                        void onDisplayConnect(IO::Event event);
//                        void onDisplayDisconnect(IO::Event event);

                        enum TYPE {
                            DISPLAY = 0,
                            SCREEN = 1
                        };
                    protected:
                        GraphicsDevice(const char *name);
                        virtual ~GraphicsDevice();
                    private:
                        friend class Displays::Screen;
                        friend class Managers::DeviceManagers::GraphicsManager;
                        List displays;
                        uint8 type;

                        void systemCreateDisplay(const char *name, uint8 type);
                        void systemDestroyDisplay();
                };
            }
        }
    }
}

#include "Displays/Screen.h"

#endif

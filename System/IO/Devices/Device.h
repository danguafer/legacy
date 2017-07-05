//!Complete

#ifndef SILEXARS_SYSTEM_IO_DEVICES_DEVICE_H_
#define SILEXARS_SYSTEM_IO_DEVICES_DEVICE_H_

#include <Veritas/Definitions/Definitions.h>
#include "../../IO/Communicator.h"

#include <cstring>

namespace Silexars {
    namespace System {
        namespace Managers { class DeviceManager; class WindowManager; }
        namespace UI { class Window; class GLContext; }

        namespace IO {
            namespace Devices {
                class Device : public Communicator {
                    public:
                        Device(const char *name);
                        ~Device();

                        const char* getName() const;

                        uint8 getCommunicatorType() const;

                        virtual uint8 getDeviceType() const = 0;
                        enum TYPE { UNKNOWN, DISPLAY, SCREEN, AUDIO, NETWORK, SENSOR };

                        uint8 getStatus() const;
                    protected:
                        friend class UI::Window;
                        friend class UI::GLContext;
                        friend class Managers::WindowManager;
                        friend class Managers::DeviceManager;

                        Handle id;

                        char name[32];

                        uint32 write(const void *data, uint32 size);
                        uint32 read(void *data, uint32 size);
                        uint32 peek(void *data, uint32 size) const;

                        uint32 canWrite() const;
                        uint32 canRead() const;
                };
            }
        }
    }
}

#endif

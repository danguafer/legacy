#ifndef SILEXARS_SYSTEM_IO_DEVICES_DISPLAYS_DISPLAY_H_
#define SILEXARS_SYSTEM_IO_DEVICES_DISPLAYS_DISPLAY_H_

#include "../Device.h"

namespace Silexars {
    namespace System {
        namespace IO {
            namespace Devices {
                namespace Displays {
                    class Display : public Device {
                        public:
                            Display(const char *name);
                    };
                }
            }
        }
    }
}

#endif

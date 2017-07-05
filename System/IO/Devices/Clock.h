//!Complete

#ifndef SILEXARS_MANAGEMENT_DEVICES_CLOCK_H_
#define SILEXARS_MANAGEMENT_DEVICES_CLOCK_H_

#include <Veritas/Definitions/Definitions.h>
#include "Device.h"

namespace Silexars {
    namespace System {
        namespace IO {
            namespace Devices {
                class Clock : public Device {
                    public:
                        static uint64 getTime();
                        static uint64 getTime(uint64 precision);

                        static uint32 getYear();
                        static uint8 getMonth();
                        static uint8 getDay();
                        static uint8 getHours();
                        static uint8 getMinutes();
                        static uint8 getSeconds();
                        static int8 getTimezone();
                };
            }
        }
    }
}

#endif

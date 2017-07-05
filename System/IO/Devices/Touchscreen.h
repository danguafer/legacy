//!Complete
#ifndef SILEXARS_MANAGEMENT_DEVICES_TOUCHSCREEN_H_
#define SILEXARS_MANAGEMENT_DEVICES_TOUCHSCREEN_H_

#include "Device.h"
#include <list>

namespace Silexars {
    namespace System {
        namespace UI { class Window; }
        namespace IO {
            namespace Devices {
                class Touchscreen : public Device {
                    public:
                        class Touch;
                        enum MOUSE { LMOUSE = 101, MMOUSE, RMOUSE };
                    private:
                        typedef std::list<Touch*> List;
                        static std::list<Touch*> touches;

                    public:
                        typedef List::iterator iterator;
                        static iterator begin();
                        static iterator end();
                        static uint32 size();
                };
            }
        }
    }
}

#include "Touchscreen.Touch.h"

#endif

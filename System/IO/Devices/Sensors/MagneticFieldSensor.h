#ifndef SILEXARS_SYSTEM_IO_DEVICES_SENSORS_MAGNETICFIELDSENSOR_H_
#define SILEXARS_SYSTEM_IO_DEVICES_SENSORS_MAGNETICFIELDSENSOR_H_

#include "../Sensor.h"
#include <Veritas/Math/vec3.h>

namespace Silexars {
    namespace System {
        namespace Managers {
            namespace DeviceManagers {
                class SensorManager;
            }
        }
        namespace IO {
            namespace Devices {
                namespace Sensors {
                    class MagneticFieldSensor : public Sensor {
                        public:
                            Math::vec3 getVector() const;
                        private:
                            MagneticFieldSensor(Managers::DeviceManagers::SensorManager* sensorManager);
                            ~MagneticFieldSensor();

                            friend class Managers::DeviceManagers::SensorManager;
                            Math::vec3 vector;
                    };
                }
            }
        }
    }
}

#endif

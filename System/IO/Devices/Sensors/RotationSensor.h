#ifndef SILEXARS_SYSTEM_IO_DEVICES_SENSORS_ROTATIONSENSOR_H_
#define SILEXARS_SYSTEM_IO_DEVICES_SENSORS_ROTATIONSENSOR_H_

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
                    class RotationSensor : public Sensor {
                        public:
                            Math::vec3 getVector() const;
                        private:
                            RotationSensor(Managers::DeviceManagers::SensorManager* sensorManager);
                            ~RotationSensor();

                            friend class Managers::DeviceManagers::SensorManager;
                            Math::vec3 vector;
                    };
                }
            }
        }
    }
}

#endif

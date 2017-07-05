#ifndef SILEXARS_SYSTEM_IO_DEVICES_SENSORS_ACCELERATIONSENSOR_H_
#define SILEXARS_SYSTEM_IO_DEVICES_SENSORS_ACCELERATIONSENSOR_H_

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
                    class AccelerationSensor : public Sensor {
                        public:                        
                            Math::vec3 getVector() const;
                        private:
                            AccelerationSensor(Managers::DeviceManagers::SensorManager* sensorManager);
                            ~AccelerationSensor();

                            friend class Managers::DeviceManagers::SensorManager;
                            Math::vec3 vector;
                    };
                }
            }
        }
    }
}

#endif

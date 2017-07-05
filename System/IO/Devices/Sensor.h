#ifndef SILEXARS_SYSTEM_IO_DEVICES_SENSOR_H_
#define SILEXARS_SYSTEM_IO_DEVICES_SENSOR_H_

#include "Device.h"

namespace Silexars {
    namespace System {
        namespace Managers { namespace DeviceManagers { class SensorManager; } }
        namespace IO {
            namespace Devices {
                class Sensor : public Device {
                    public:
                        uint8 getDeviceType() const;

                        void enable();
                        void disable();
                        bool isEnabled() const;

                        enum TYPE { ACCELERATION_SENSOR, ROTATION_SENSOR, MAGNETIC_FIELD_SENSOR };
                    protected:
                        Sensor(Managers::DeviceManagers::SensorManager* sensorManager, uint8 SensorType);
                        ~Sensor();

                        bool isenabled;
                    private:
                        void systemCSensor(Managers::DeviceManagers::SensorManager* sensorManager, uint8 sensorType);
                        void systemDSensor();
                        void systemEnable();
                        void systemDisable();
                };
            }
        }
    }
}

#endif

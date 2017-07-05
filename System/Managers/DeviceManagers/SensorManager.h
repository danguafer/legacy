#ifndef SILEXARS_SYSTEM_MANAGERS_DEVICEMANAGERS_SENSORMANAGER_H_
#define SILEXARS_SYSTEM_MANAGERS_DEVICEMANAGERS_SENSORMANAGER_H_

#include "../../IO/Devices/Sensors/Sensors.h"

namespace Silexars {
    namespace System {
        namespace Managers {
            class DeviceManager;
            namespace DeviceManagers {
                class SensorManager {
                    public:
                        IO::Devices::Sensors::AccelerationSensor* getDefaultAccelerationSensor() const;
                        IO::Devices::Sensors::RotationSensor* getDefaultRotationSensor() const;
                        IO::Devices::Sensors::MagneticFieldSensor* getDefaultMagneticFieldSensor() const;
                    private:
                        Handle id;

                        friend class Managers::DeviceManager;

                        void systemCSensorManager();
                        void systemDSensorManager();

                        void manage();
                        void systemManage();

                        SensorManager();
                        ~SensorManager();

                        friend class IO::Devices::Sensor;
                        IO::Devices::Sensors::AccelerationSensor *accelerationSensor;
                        IO::Devices::Sensors::RotationSensor *orientationSensor;
                        IO::Devices::Sensors::MagneticFieldSensor *magneticFieldSensor;

                        static int acallback(int fd, int events, void *data);
                };
            }
        }
    }
}

#endif

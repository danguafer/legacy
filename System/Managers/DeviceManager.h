//!Complete

#ifndef SILEXARS_SYSTEM_MANAGERS_DEVICEMANAGER_H_
#define SILEXARS_SYSTEM_MANAGERS_DEVICEMANAGER_H_

#include <Veritas/Definitions/Definitions.h>
#include "../IO/Devices/Devices.h"
#include "DeviceManagers/DeviceManagers.h"

#include <list>

namespace Silexars {
    namespace System {
        namespace Managers {
            class Manager;
            class DeviceManager {
                private:
                    typedef std::list<IO::Devices::Device*> List;
                public:
                    typedef List::iterator iterator;

                    iterator begin();
                    iterator end();
                    uint32 size() const;

                    DeviceManagers::GraphicsManager* getDisplayManager() const;
                    DeviceManagers::NetworkManager* getNetworkManager() const;
                    DeviceManagers::SensorManager* getSensorManager() const;
                private:
                    friend class Manager;
                    void manage();

                    List devices;

                    DeviceManagers::GraphicsManager displayManager;
                    DeviceManagers::NetworkManager networkManager;
                    DeviceManagers::SensorManager sensorManager;

                    DeviceManager();
                    ~DeviceManager();
            };
        }
    }
}

#endif

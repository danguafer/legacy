#ifndef SILEXARS_SYSTEM_MANAGERS_DEVICEMANAGERS_NETWORKMANAGER_H
#define SILEXARS_SYSTEM_MANAGERS_DEVICEMANAGERS_NETWORKMANAGER_H

#include <list>
#include "../../IO/Devices/Devices.h"

namespace Silexars {
    namespace System {
        namespace Managers {
            namespace DeviceManagers {
                class NetworkManager {
                    private:
                        typedef std::list<IO::Devices::NetworkDevice*> List;
                    public:
                        typedef List::iterator iterator;

                        iterator begin();
                        iterator end();
                        uint32 size() const;
                    private:
                        void manage();

                        friend class Managers::DeviceManager;
                        List devices;

                        NetworkManager();
                        ~NetworkManager();

                        void systemCreateNetworkManager();
                        void systemDestroyNetworkManager();
                };
            }
        }
    }
}

#endif // ETHERNETMANAGER_H

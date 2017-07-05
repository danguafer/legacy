//!Complete

#ifndef SILEXARS_SYSTEM_DEVICES_NETWORKDEVICE_H
#define SILEXARS_SYSTEM_DEVICES_NETWORKDEVICE_H

#include <list>
#include <Veritas/Definitions/Definitions.h>
#include "../Net/NetNode.h"
#include "Device.h"

namespace Silexars {
    namespace System {
        namespace Managers { namespace DeviceManagers { class NetworkManager; } }
        namespace IO {
            namespace Devices {
                class NetworkDevice : public Device {
                    private:
                        typedef std::list<IO::Net::NetNode*> List;
                    public:
                        typedef List::iterator iterator;

                        iterator begin();
                        iterator end();
                        uint32 size() const;

                        uint8 getDeviceType() const;
                    private:
                        friend class Managers::DeviceManagers::NetworkManager;

                        NetworkDevice(const char* name);
                        ~NetworkDevice();

                        List nodes;

                        void systemCreateNetworkAdapter(const char* name);
                };
            }
        }
    }
}

#endif

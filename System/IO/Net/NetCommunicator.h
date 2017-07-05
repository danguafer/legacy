#ifndef SILEXARS_SYSTEM_IO_NET_NETCOMMUNICATOR_H
#define SILEXARS_SYSTEM_IO_NET_NETCOMMUNICATOR_H

#include "../Communicator.h"
#include "NetNode.h"
#include "../../Utils/AutoManager.h"

namespace Silexars {
    namespace System {
        namespace IO {
            namespace Net {
                class NetListener;
                class NetCommunicator : public Communicator {
                    public:
                        NetCommunicator(NetCommunicator *parent, NetNode *node);
                        virtual ~NetCommunicator();

                        uint8 getCommunicatorType() const;
                        NetCommunicator* getParent() const;

                        virtual uint8 getLayer() const = 0;
                        virtual uint8 getProtocol() const = 0;
                    protected:
                        NetCommunicator(NetListener *listener, NetCommunicator *parent, NetNode *node);
                    private:
                        Utils::AutoManager<NetCommunicator> parent;
                };
            }
        }
    }
}

#endif // SOCKETCOMMUNICATOR_H

#ifndef SILEXARS_SYSTEM_IO_NET_NETLISTENER_H
#define SILEXARS_SYSTEM_IO_NET_NETLISTENER_H

#include "../Listener.h"
#include "NetNode.h"

namespace Silexars {
    namespace System {
        namespace IO {
            namespace Net {
                class NetListener : public Listener {
                    public:
                        NetListener(NetListener *parent, NetNode *node);
                        virtual ~NetListener();

                        uint8 getType() const;
                        NetListener* getParent() const;

                        virtual uint8 getLayer() const = 0;
                        virtual uint8 getProtocol() const = 0;
                    private:
                        NetListener *parent;
                };
            }
        }
    }
}

#endif // NETLISTENER_H

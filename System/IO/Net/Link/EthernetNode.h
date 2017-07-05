#ifndef SILEXARS_SYSTEM_IO_NET_LINK_ETHERNETNODE_H
#define SILEXARS_SYSTEM_IO_NET_LINK_ETHERNETNODE_H

#include "LinkNode.h"

namespace Silexars {
    namespace System {
        namespace IO {
            namespace Devices { class NetworkDevice; }
            namespace Net {
                namespace Link {
                    class EthernetNode : public LinkNode {
                        public:
                            EthernetNode(uint8 a0, uint8 a1, uint8 a2, uint8 a3, uint8 a4, uint8 a5);

                            uint8 getProtocol() const;

                            uint8 getGroup(uint8 g) const;
                        private:
                            friend class Devices::NetworkDevice;

                            EthernetNode(void *addr);
                            void* tosockaddr(void *addr);

                            uint8 addr[6];
                    };
                }
            }
        }
    }
}

#endif // ETHERNETNODE_H

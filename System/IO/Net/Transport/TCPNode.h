#ifndef SILEXARS_SYSTEM_IO_NET_TRANSPORT_TCPNODE_H
#define SILEXARS_SYSTEM_IO_NET_TRANSPORT_TCPNODE_H

#include "TransportNode.h"

namespace Silexars {
    namespace System {
        namespace IO {
            namespace Net {
                namespace Transport {
                    class TCPNode : public TransportNode {
                        public:
                            TCPNode(uint16 port);

                            uint16 getPort() const;

                            uint8 getProtocol() const;
                        private:
                            uint16 port;
                    };
                }
            }
        }
    }
}

#endif // TCPNODE_H

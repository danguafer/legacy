#ifndef SILEXARS_SYSTEM_IO_NET_INTERNET_IPV4NODE_H
#define SILEXARS_SYSTEM_IO_NET_INTERNET_IPV4NODE_H

#include "InternetNode.h"

namespace Silexars {
    namespace System {
        namespace IO {
            namespace Devices { class NetworkDevice; }
            namespace Net {
                namespace Transport {
                    class TCPListener;
                    class UDPListener;
                    class TCPCommunicator;
                    class UDPCommunicator;
                }
                namespace Internet {
                    class IPV4Node : public InternetNode {
                        public:
                            IPV4Node(uint8 a0, uint8 a1, uint8 a2, uint8 a3);

                            uint8 getProtocol() const;

                            uint8 getGroup(uint8 g) const;
                        private:
                            friend class Transport::TCPListener;
                            friend class Transport::UDPListener;
                            friend class Transport::UDPCommunicator;
                            friend class Transport::TCPCommunicator;
                            friend class Devices::NetworkDevice;

                            IPV4Node(void* saddr);
                            uint8 addr[4];
                    };
                }
            }
        }
    }
}

#endif // IPV4NODE_H

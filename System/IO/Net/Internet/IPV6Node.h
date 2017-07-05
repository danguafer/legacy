#ifndef SILEXARS_SYSTEM_IO_NET_INTERNET_IPV6NODE_H
#define SILEXARS_SYSTEM_IO_NET_INTERNET_IPV6NODE_H

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
                    class IPV6Node : public InternetNode {
                        public:
                            IPV6Node(uint16 a0, uint16 a1, uint16 a2, uint16 a3, uint16 a4, uint16 a5, uint16 a6, uint16 a7);

                            uint8 getProtocol() const;

                            uint16 getGroup(uint8 g) const;
                        private:
                            friend class Devices::NetworkDevice;
                            friend class Transport::TCPListener;
                            friend class Transport::UDPListener;
                            friend class Transport::UDPCommunicator;
                            friend class Transport::TCPCommunicator;

                            IPV6Node(void* saddr);
                            void* createsockaddr(uint32* length, uint16 port = 0);

                            uint16 addr[8];
                    };
                }
            }
        }
    }
}

#endif // IPV6NODE_H

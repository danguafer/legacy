#ifndef SILEXARS_SYSTEM_IO_NET_TRANSPORT_TCPLISTENER_H
#define SILEXARS_SYSTEM_IO_NET_TRANSPORT_TCPLISTENER_H

#include "TransportListener.h"
#include "TCPNode.h"

namespace Silexars {
    namespace System {
        namespace IO {
            namespace Net {
                namespace Transport {
                    class TCPListener : public TransportListener {
                        public:
                            TCPListener(Internet::InternetListener *parent, TCPNode *node);
                            ~TCPListener();

                            Communicator* accept();

                            uint8 getProtocol() const;
                        private:
                            Handle id;

                            uint8 addr[32];
                            uint32 addrlen;
                    };
                }
            }
        }
    }
}

#endif // TCPLISTENER_H

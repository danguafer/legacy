#ifndef SILEXARS_SYSTEM_IO_NET_TRANSPORT_TCPCOMMUNICATOR_H
#define SILEXARS_SYSTEM_IO_NET_TRANSPORT_TCPCOMMUNICATOR_H

#include "TransportCommunicator.h"
#include "TCPNode.h"
#include "../Internet/InternetCommunicator.h"

namespace Silexars {
    namespace System {
        namespace IO {
            namespace Net {
                namespace Transport {
                    class TCPListener;
                    class TCPCommunicator : public TransportCommunicator {
                        public:
                            TCPCommunicator(Internet::InternetCommunicator *parent, TCPNode *node);
                            ~TCPCommunicator();

                            uint8 getStatus() const;

                            uint32 write(const void *data, uint32 size);
                            uint32 read(void *data, uint32 size);
                            uint32 peek(void *data, uint32 size) const;

                            uint32 canWrite() const;
                            uint32 canRead() const;

                            uint8 getProtocol() const;
                        private:
                            friend class TCPListener;
                            TCPCommunicator(void* acceptedSocket, Internet::InternetCommunicator *parent, TCPNode *node);

                            Handle id;
                            bool islistening;
                            uint32 read(void *data, uint32 size, bool remove);
                    };
                }
            }
        }
    }
}

#endif // TCPCOMMUNICATOR_H

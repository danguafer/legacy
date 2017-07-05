#ifndef SILEXARS_SYSTEM_IO_NET_INTERNET_IPV4COMMUNICATOR_H
#define SILEXARS_SYSTEM_IO_NET_INTERNET_IPV4COMMUNICATOR_H

#include "InternetCommunicator.h"
#include "IPV4Node.h"

namespace Silexars {
    namespace System {
        namespace IO {
            namespace Net {
                namespace Transport {
                    class UDPListener;
                    class TCPListener;
                }
                namespace Internet {
                    class IPV4Listener;
                    class IPV4Communicator : public InternetCommunicator {
                        public:
                            IPV4Communicator(Link::LinkCommunicator *parent, IPV4Node *node);
                            IPV4Communicator(IPV4Node *node);

                            uint8 getStatus() const;

                            uint32 write(const void *data, uint32 size);
                            uint32 read(void *data, uint32 size);
                            uint32 peek(void *data, uint32 size) const;

                            uint32 canWrite() const;
                            uint32 canRead() const;

                            uint8 getProtocol() const;
                        private:
                            friend class IPV4Listener;
                            friend class Transport::UDPListener;
                            friend class Transport::TCPListener;
                            IPV4Communicator(IPV4Listener *listener, Link::LinkCommunicator *parent, IPV4Node *node);
                            IPV4Communicator(IPV4Listener *listener, IPV4Node *node);
                    };
                }
            }
        }
    }
}

#endif // IPV4COMMUNICATOR_H

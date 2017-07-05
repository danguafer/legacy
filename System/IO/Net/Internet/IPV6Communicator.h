#ifndef SILEXARS_SYSTEM_IO_NET_INTERNET_IPV6COMMUNICATOR_H
#define SILEXARS_SYSTEM_IO_NET_INTERNET_IPV6COMMUNICATOR_H

#include "InternetCommunicator.h"
#include "IPV6Node.h"

namespace Silexars {
    namespace System {
        namespace IO {
            namespace Net {
                namespace Transport {
                    class UDPListener;
                    class TCPListener;
                }
                namespace Internet {
                    class IPV6Listener;
                    class IPV6Communicator : public InternetCommunicator {
                        public:
                            IPV6Communicator(Link::LinkCommunicator *parent, IPV6Node *node);
                            IPV6Communicator(IPV6Node *node);

                            uint8 getStatus() const;

                            uint32 write(const void *data, uint32 size);
                            uint32 read(void *data, uint32 size);
                            uint32 peek(void *data, uint32 size) const;

                            uint32 canWrite() const;
                            uint32 canRead() const;

                            uint8 getProtocol() const;
                        private:
                            friend class Transport::UDPListener;
                            friend class Transport::TCPListener;

                            IPV6Communicator(IPV6Listener *listener, Link::LinkCommunicator *parent, IPV6Node *node);
                            IPV6Communicator(IPV6Listener *listener, IPV6Node *node);
                    };
                }
            }
        }
    }
}

#endif // IPV6COMMUNICATOR_H

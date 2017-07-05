#ifndef SILEXARS_SYSTEM_IO_NET_INTERNET_IPV4LISTENER_H
#define SILEXARS_SYSTEM_IO_NET_INTERNET_IPV4LISTENER_H

#include "InternetListener.h"
#include "IPV4Node.h"

namespace Silexars {
    namespace System {
        namespace IO {
            namespace Net {
                namespace Internet {
                    class IPV4Listener : public InternetListener {
                        public:
                            IPV4Listener(Link::LinkListener *parent, IPV4Node *node);
                            IPV4Listener(IPV4Node *node);

                            Communicator* accept();

                            uint8 getProtocol() const;
                    };
                }
            }
        }
    }
}

#endif // IPV4LISTENER_H

#ifndef SILEXARS_SYSTEM_IO_NET_INTERNET_IPV6LISTENER_H
#define SILEXARS_SYSTEM_IO_NET_INTERNET_IPV6LISTENER_H

#include "InternetListener.h"
#include "IPV6Node.h"

namespace Silexars {
    namespace System {
        namespace IO {
            namespace Net {
                namespace Internet {
                    class IPV6Listener : public InternetListener {
                        public:
                            IPV6Listener(Link::LinkListener *parent, IPV6Node *node);
                            IPV6Listener(IPV6Node* node);

                            Communicator* accept();

                            uint8 getProtocol() const;
                    };
                }
            }
        }
    }
}

#endif // IPV6LISTENER_H

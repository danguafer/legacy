#ifndef SILEXARS_SYSTEM_IO_NET_INTERNET_DOMAINNODE_H
#define SILEXARS_SYSTEM_IO_NET_INTERNET_DOMAINNODE_H

#include "InternetNode.h"
#include "IPV4Node.h"
#include "IPV6Node.h"

namespace Silexars {
    namespace System {
        namespace IO {
            namespace Net {
                namespace Internet {
                    class DomainNode : public InternetNode {
                        public:
                            DomainNode(const char* name);
                            ~DomainNode();

                            const char* getName() const;
                            IPV4Node* getIPV4Node() const;
                            IPV6Node* getIPV6Node() const;

                            uint8 getProtocol() const;
                        private:
                            char* name;
                            IPV4Node *ipv4;
                            IPV6Node *ipv6;
                    };
                }
            }
        }
    }
}

#endif // DOMAINNODE_H

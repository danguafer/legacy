#ifndef SILEXARS_SYSTEM_IO_NET_NETNODE_H
#define SILEXARS_SYSTEM_IO_NET_NETNODE_H

#include "../Node.h"

namespace Silexars {
    namespace System {
        namespace IO {
            namespace Net {
                class NetNode : public Node {
                    public:
                        virtual ~NetNode();

                        uint8 getNodeType() const;
                        virtual uint8 getLayer() const = 0;
                        virtual uint8 getProtocol() const = 0;

                        enum LAYER { PHYSICAL, LINK, INTERNET, TRANSPORT, APPLICATION };
                };
            }
        }
    }
}

#endif // SOCKETNODE_H

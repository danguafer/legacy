#ifndef SILEXARS_SYSTEM_IO_NET_LINK_LINKNODE_H
#define SILEXARS_SYSTEM_IO_NET_LINK_LINKNODE_H

#include "../NetNode.h"

namespace Silexars {
    namespace System {
        namespace IO {
            namespace Net {
                namespace Link {
                    class LinkNode : public NetNode {
                        public:
                            virtual ~LinkNode();

                            uint8 getLayer() const;

                            enum PROTOCOLS { ETHERNET };
                    };
                }
            }
        }
    }
}

#endif // LINKNODE_H

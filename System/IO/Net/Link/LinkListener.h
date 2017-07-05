#ifndef SILEXARS_SYSTEM_IO_NET_LINK_LINKLISTENER_H
#define SILEXARS_SYSTEM_IO_NET_LINK_LINKLISTENER_H

#include "../NetListener.h"
#include "LinkNode.h"

namespace Silexars {
    namespace System {
        namespace IO {
            namespace Net {
                namespace Link {
                    class LinkListener : public NetListener, public virtual LinkNode {
                        public:
                            LinkListener(LinkNode *node);
                            virtual ~LinkListener();

                            uint8 getLayer() const;
                    };
                }
            }
        }
    }
}

#endif // LINKLISTENER_H

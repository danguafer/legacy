#ifndef SILEXARS_SYSTEM_IO_NET_LINK_LINKCOMMUNICATOR_H
#define SILEXARS_SYSTEM_IO_NET_LINK_LINKCOMMUNICATOR_H

#include "../NetCommunicator.h"
#include "LinkNode.h"

namespace Silexars {
    namespace System {
        namespace IO {
            namespace Net {
                namespace Link {
                    class LinkCommunicator : public NetCommunicator {
                        public:
                            LinkCommunicator(LinkNode *node);
                            virtual ~LinkCommunicator();

                            uint8 getLayer() const;
                    };
                }
            }
        }
    }
}

#endif // LINKCOMMUNICATOR_H

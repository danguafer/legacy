#ifndef SILEXARS_SYSTEM_IO_NET_TRANSPORT_TRANSPORTNODE_H
#define SILEXARS_SYSTEM_IO_NET_TRANSPORT_TRANSPORTNODE_H

#include "../NetNode.h"

namespace Silexars {
    namespace System {
        namespace IO {
            namespace Net {
                namespace Transport {
                    class TransportNode : public NetNode {
                        public:
                            virtual ~TransportNode();

                            uint8 getLayer() const;

                            enum PROTOCOLS { TCP, UDP };
                    };
                }
            }
        }
    }
}

#endif // TRANSPORTNODE_H

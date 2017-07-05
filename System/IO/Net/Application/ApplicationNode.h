#ifndef SILEXARS_SYSTEM_IO_NET_APPLICATION_APPLICATIONNODE_H
#define SILEXARS_SYSTEM_IO_NET_APPLICATION_APPLICATIONNODE_H

#include "../NetNode.h"

namespace Silexars {
    namespace System {
        namespace IO {
            namespace Net {
                namespace Application {
                    class ApplicationNode : public NetNode {
                        public:
                            virtual ~ApplicationNode();

                            uint8 getLayer() const;

                            enum PROTOCOLS { /* HTTP, WEBSOCKET */ };
                    };
                }
            }
        }
    }
}

#endif // APPLICATIONNODE_H

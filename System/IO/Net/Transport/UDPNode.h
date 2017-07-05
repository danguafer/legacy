#pragma once

#include "TransportNode.h"

namespace Silexars {
    namespace System {
        namespace IO {
            namespace Net {
                namespace Transport {
                    class UDPNode : public TransportNode {
                        public:
                            UDPNode(uint16 port);

                            uint16 getPort() const;

                            uint8 getProtocol() const;
                        private:
                            uint16 port;
                    };
                }
            }
        }
    }
}

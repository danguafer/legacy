#pragma once

#include "TransportListener.h"
#include "UDPNode.h"

namespace Silexars {
    namespace System {
        namespace IO {
            namespace Net {
                namespace Transport {
                    class UDPListener : public TransportListener {
                        public:
                            UDPListener(Internet::InternetListener *parent, UDPNode *node);
                            ~UDPListener();

                            Communicator* accept();

                            uint8 getProtocol() const;
                        private:
                            Handle id;
                    };
                }
            }
        }
    }
}

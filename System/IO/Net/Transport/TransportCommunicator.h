#ifndef SILEXARS_SYSTEM_IO_NET_TRANSPORT_TRANSPORTCOMMUNICATOR_H
#define SILEXARS_SYSTEM_IO_NET_TRANSPORT_TRANSPORTCOMMUNICATOR_H

#include "../NetCommunicator.h"
#include "../Internet/InternetCommunicator.h"
#include "TransportNode.h"

namespace Silexars {
    namespace System {
        namespace IO {
            namespace Net {
                namespace Transport {
                    class TransportListener;
                    class TransportCommunicator : public NetCommunicator {
                        public:
                            TransportCommunicator(Internet::InternetCommunicator *parent, TransportNode* node);
                            virtual ~TransportCommunicator();

                            uint8 getLayer() const;
                        protected:
                            TransportCommunicator(TransportListener *listener, Internet::InternetCommunicator *parent, TransportNode *node);
                    };
                }
            }
        }
    }
}

#endif // TRANSPORTCOMMUNICATOR_H

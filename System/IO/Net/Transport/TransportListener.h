#ifndef SILEXARS_SYSTEM_IO_NET_TRANSPORT_TRANSPORTLISTENER_H
#define SILEXARS_SYSTEM_IO_NET_TRANSPORT_TRANSPORTLISTENER_H

#include "../NetListener.h"
#include "../Internet/InternetListener.h"
#include "TransportNode.h"

namespace Silexars {
    namespace System {
        namespace IO {
            namespace Net {
                namespace Transport {
                    class TransportListener : public NetListener {
                        public:
                            TransportListener(Internet::InternetListener *parent, TransportNode *node);
                            virtual ~TransportListener();

                            uint8 getLayer() const;
                    };
                }
            }
        }
    }
}

#endif // TRANSPORTLISTENER_H

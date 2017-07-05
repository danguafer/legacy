#ifndef SILEXARS_SYSTEM_IO_NET_APPLICATION_APPLICATIONLISTENER_H
#define SILEXARS_SYSTEM_IO_NET_APPLICATION_APPLICATIONLISTENER_H

#include "../NetListener.h"
#include "../Transport/TransportListener.h"
#include "ApplicationNode.h"

namespace Silexars {
    namespace System {
        namespace IO {
            namespace Net {
                namespace Application {
                    class ApplicationListener : public NetListener {
                        public:
                            ApplicationListener(Transport::TransportListener *parent, ApplicationNode *node);
                            virtual ~ApplicationListener();

                            uint8 getLayer() const;
                    };
                }
            }
        }
    }
}

#endif // APPLICATIONLISTENER_H

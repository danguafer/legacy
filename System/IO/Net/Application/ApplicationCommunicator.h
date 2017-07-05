#ifndef SILEXARS_SYSTEM_IO_NET_APPLICATION_APPLICATIONCOMMUNICATOR_H
#define SILEXARS_SYSTEM_IO_NET_APPLICATION_APPLICATIONCOMMUNICATOR_H

#include "../NetCommunicator.h"
#include "../Transport/TransportCommunicator.h"
#include "ApplicationNode.h"

namespace Silexars {
    namespace System {
        namespace IO {
            namespace Net {
                namespace Application {
                    class ApplicationCommunicator : public NetCommunicator {
                        public:
                            ApplicationCommunicator(Transport::TransportCommunicator *parent, ApplicationNode *node);
                            virtual ~ApplicationCommunicator();

                            uint8 getLayer() const;
                    };
                }
            }
        }
    }
}

#endif // APPLICATIONCOMMUNICATOR_H

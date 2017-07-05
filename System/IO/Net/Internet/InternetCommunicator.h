#ifndef SILEXARS_SYSTEM_IO_NET_INTERNET_INTERNETCOMMUNICATOR_H
#define SILEXARS_SYSTEM_IO_NET_INTERNET_INTERNETCOMMUNICATOR_H

#include "../NetCommunicator.h"
#include "../Link/LinkCommunicator.h"
#include "InternetNode.h"

namespace Silexars {
    namespace System {
        namespace IO {
            namespace Net {
                namespace Internet {
                    class InternetListener;
                    class InternetCommunicator : public NetCommunicator {
                        public:
                            InternetCommunicator(Link::LinkCommunicator *parent, InternetNode *node);
                            virtual ~InternetCommunicator();

                            uint8 getLayer() const;
                        protected:
                            InternetCommunicator(InternetListener *listener, Link::LinkCommunicator *parent, InternetNode *node);
                    };
                }
            }
        }
    }
}

#endif // INTERNETCOMMUNICATOR_H

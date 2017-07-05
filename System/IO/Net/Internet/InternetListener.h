#ifndef SILEXARS_SYSTEM_IO_NET_INTERNET_INTERNETLISTENER_H
#define SILEXARS_SYSTEM_IO_NET_INTERNET_INTERNETLISTENER_H

#include "../NetListener.h"
#include "../Link/LinkListener.h"
#include "InternetNode.h"

namespace Silexars {
    namespace System {
        namespace IO {
            namespace Net {
                namespace Internet {
                    class InternetListener : public NetListener {
                        public:
                            InternetListener(Link::LinkListener *parent, InternetNode *node);
                            virtual ~InternetListener();

                            uint8 getLayer() const;
                    };
                }
            }
        }
    }
}

#endif // INTERNETLISTENER_H

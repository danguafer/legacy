#ifndef SILEXARS_SYSTEM_IO_NET_INTERNET_INTERNETNODE_H
#define SILEXARS_SYSTEM_IO_NET_INTERNET_INTERNETNODE_H

#include "../NetNode.h"

namespace Silexars {
    namespace System {
        namespace IO {
            namespace Net {
                namespace Internet {
                    class InternetNode : public NetNode {
                        public:
                            virtual ~InternetNode();

                            uint8 getLayer() const;

                            enum PROTOCOLS { UNKNOWN, IPV4, IPV6 };
                    };
                }
            }
        }
    }
}

#endif // INTERNETNODE_H

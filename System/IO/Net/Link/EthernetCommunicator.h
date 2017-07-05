#ifndef SILEXARS_SYSTEM_IO_NET_LINK_ETHERNETCOMMUNICATOR_H
#define SILEXARS_SYSTEM_IO_NET_LINK_ETHERNETCOMMUNICATOR_H

#include "LinkCommunicator.h"
#include "EthernetNode.h"

namespace Silexars {
    namespace System {
        namespace IO {
            namespace Net {
                namespace Link {
                    class EthernetCommunicator : public LinkCommunicator {
                        public:
                            EthernetCommunicator(EthernetNode *node);

                            uint8 getStatus() const;

                            uint32 write(void *data, uint32 size);
                            uint32 read(void *data, uint32 size);
                            uint32 peek(void *data, uint32 size) const;

                            uint32 canWrite() const;
                            uint32 canRead() const;

                            uint8 getProtocol() const;
                    };
                }
            }
        }
    }
}

#endif // ETHERNETCOMMUNICATOR_H

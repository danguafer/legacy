#pragma once

#include "TransportCommunicator.h"
#include "UDPNode.h"
#include "../Internet/InternetCommunicator.h"

namespace Silexars {
    namespace System {
        namespace IO {
            namespace Net {
                namespace Transport {
                    class UDPListener;
                    class UDPCommunicator : public TransportCommunicator {
                        public:
                            UDPCommunicator(Internet::InternetCommunicator *parent, UDPNode *node);
                            ~UDPCommunicator();

                            uint8 getStatus() const;

                            uint32 write(const void *data, uint32 size);
                            uint32 read(void *data, uint32 size);
                            uint32 peek(void *data, uint32 size) const;

                            uint32 canWrite() const;
                            uint32 canRead() const;

                            uint8 getProtocol() const;
                        private:
                            friend class UDPListener;

                            UDPCommunicator(UDPListener *listener, Internet::InternetCommunicator *parent, UDPNode *node);

                            Handle id;
                            bool islistening;
                            uint32 read(void *data, uint32 size, bool remove);
                    };
                }
            }
        }
    }
}

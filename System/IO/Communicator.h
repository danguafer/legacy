//!Incomplete
//!Implement events and event manager

#pragma once

#include <Veritas/Definitions/Definitions.h>
#include "../Utils/AutoManager.h"
#include "Node.h"
#include "Message.h"

namespace Silexars {
    namespace System {
        namespace IO {
            class Listener;
            class Communicator : public Message::Listener {
                public:
                    Communicator(Node* node);
                    virtual ~Communicator();

                    virtual uint8 getCommunicatorType() const = 0;

                    Node* getNode() const;
                    virtual uint8 getStatus() const = 0;

                    void setConnectionTimeout(uint32 milliseconds);
                    uint32 getConnectionTimeout() const;

                    virtual uint32 write(const void* data, uint32 size) = 0;
                    virtual uint32 read(void* data, uint32 size) = 0;
                    virtual uint32 peek(void* data, uint32 size) const = 0;

                    virtual uint32 canWrite() const = 0;
                    virtual uint32 canRead() const = 0;

                    enum STATUS { DISCONNECTED, CONNECTING, CONNECTED };

                    void manage();
                protected:
                    uint64 lastActivity;

                    Communicator(Listener *listener, Node* node);

                    Listener *listener;
                    uint8 status;
                    Utils::AutoManager<Node> node;

                    uint32 connectionTimeout;

                    void runConnected();
                    void runDisconnected();
            };
        }
    }
}

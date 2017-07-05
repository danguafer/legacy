#pragma once

#include "Communicator.h"
#include "Node.h"
#include "Message.h"

#include <list>

namespace Silexars {
    namespace System {
        namespace IO {
            class Listener : public Message::Listener {
                public:
                    Listener(Node *node);
                    virtual ~Listener();

                    virtual uint8 getType() const = 0;

                    bool isListening() const;
                    Node* getNode() const;

                    virtual Communicator* accept() = 0;

                    void manage();
                protected:
                    Node *node;
                    bool islistening;

                    typedef std::list<Communicator*> Communicators;
                    Communicators communicators;
            };
        }
    }
}

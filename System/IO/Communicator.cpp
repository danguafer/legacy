//!Complete

#include "Communicator.h"

using namespace Silexars;
using namespace System;
using namespace IO;

#include <Veritas/System/IO/Devices/Clock.h>
using Devices::Clock;

Communicator::Communicator(Node *node) {
    listener = 0;
    status = DISCONNECTED;
    this->node = node;
    lastActivity = Clock::getTime();
    setConnectionTimeout(180000);
}
Communicator::Communicator(Listener *listener, Node *node) {
    this->listener = listener;
    status = CONNECTED;
    this->node.manage(node);
    lastActivity = Clock::getTime();
    setConnectionTimeout(180000);
}

Communicator::~Communicator() {}

Node* Communicator::getNode() const { return node; }

void Communicator::runConnected() {
    status = CONNECTED;
    Message().dispatch(this, "Connect");
    lastActivity = Clock::getTime();
}

void Communicator::runDisconnected() {
    status = DISCONNECTED;
    Message().dispatch(this, "Disconnect");
}

void Communicator::setConnectionTimeout(uint32 milliseconds) { connectionTimeout = milliseconds; }
uint32 Communicator::getConnectionTimeout() const { return connectionTimeout; }

void Communicator::manage() {
    uint64 now = Clock::getTime();

    switch (getStatus()) {
        case CONNECTED: {
            uint32 dataSize = canRead();
            if (dataSize) {
                uint8 *data = new uint8[dataSize];
                uint32 size = read(data, dataSize);
                Message().set("DataSize", size)
                         .set("Data", data)
                         .dispatch(this, "Data");
                delete[] data;
                lastActivity = now;
            }

            if (now - lastActivity > connectionTimeout) runDisconnected();
        break;
        } // END OF CONNECTED
    }
}

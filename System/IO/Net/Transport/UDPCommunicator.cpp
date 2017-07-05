#include "UDPCommunicator.h"
#include "UDPListener.h"
#include "../Internet/IPV4Node.h"
#include "../Internet/IPV6Node.h"

#include <Veritas/etc/Socket/Socket.h>

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Net;
using namespace Transport;
using namespace Internet;

using Veritas::etc::Socket;

Socket::Address* getAddress(InternetNode *node, uint16 port);

UDPCommunicator::UDPCommunicator(Internet::InternetCommunicator *parent, UDPNode *node) : TransportCommunicator(parent, node) {
    Socket* socket = new Socket(Socket::UDP);
    socket->blocking(false);

    Socket::Address *address = getAddress((InternetNode*) parent->getNode(), node->getPort());
    socket->reuseAddress(true);
    socket->connect(*address);
    delete address;

    id = (Handle) socket;

    runConnected();
}

UDPCommunicator::~UDPCommunicator() {
    delete ((Socket*) id);
}

uint32 UDPCommunicator::write(const void *data, uint32 size) {
    Socket* socket = (Socket*) id;
    int32 sent = socket->send(data, size);
    if (sent < 0) sent = 0;
    return sent;
}

uint32 UDPCommunicator::read(void *data, uint32 size) { return read(data, size, true); }
uint32 UDPCommunicator::peek(void *data, uint32 size) const { return const_cast<UDPCommunicator*>(this)->read(data, size, false); }
uint32 UDPCommunicator::read(void *data, uint32 size, bool remove) {
    Socket* socket = (Socket*) id;
    int32 read = socket->recv(data, size, !remove);
    if (read < 0) read = 0;
    return read;
}

uint32 UDPCommunicator::canWrite() const { return ((Socket*) id)->canSend(); }
uint32 UDPCommunicator::canRead() const { return ((Socket*) id)->canRecv(); }

uint8 UDPCommunicator::getProtocol() const { return TransportNode::UDP; }

uint8 UDPCommunicator::getStatus() const { return status; }

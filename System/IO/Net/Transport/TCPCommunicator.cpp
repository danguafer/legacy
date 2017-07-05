#include "TCPCommunicator.h"
#include "TCPListener.h"
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

Socket::Address* getAddress(InternetNode* node, uint16 port);

TCPCommunicator::TCPCommunicator(Internet::InternetCommunicator *parent, TCPNode *node) : TransportCommunicator(parent, node) {
    Socket *socket = new Socket(Socket::TCP);
    socket->blocking(false);

    Socket::Address *address = getAddress((InternetNode*) parent->getNode(), node->getPort());
    socket->connect(*address);
    delete address;
}

TCPCommunicator::TCPCommunicator(void *acceptedSocket, InternetCommunicator *parent, TCPNode *node) : TransportCommunicator(parent, node) {
    id = (Handle) acceptedSocket;
    runConnected();
}
TCPCommunicator::~TCPCommunicator() {
    delete ((Socket*) id);
}

uint32 TCPCommunicator::write(const void *data, uint32 size) {
    Socket *socket = (Socket*) id;
    int32 sent = socket->send(data, size);
    if (sent < 0) sent = 0;
    return sent;
    /*
    if (status == DISCONNECTED) return 0;
    if (!size) return 0;
    int sent = ::send((int) id, (char*) data, size, MSG_NOSIGNAL);
    if (sent < 0) {
        int error = errno;
        if (status == CONNECTED && error != EWOULDBLOCK && error != EINTR && error != EAGAIN) runDisconnected();
        return 0;
    } else if (status == CONNECTING) runConnected();

    return sent;
    */
}

uint32 TCPCommunicator::read(void *data, uint32 size) { return read(data, size, true); }
uint32 TCPCommunicator::peek(void *data, uint32 size) const { return const_cast<TCPCommunicator*>(this)->read(data, size, false); }
uint32 TCPCommunicator::read(void *data, uint32 size, bool remove) {
    if (getStatus() != CONNECTED) return 0;

    Socket *socket = (Socket*) id;
    int32 read = socket->recv(data, size);
    if (read < 0) read = 0;
    return read;
}

uint32 TCPCommunicator::canWrite() const { return ((Socket*) id)->canSend(); }
uint32 TCPCommunicator::canRead() const { return ((Socket*) id)->canRecv(); }

uint8 TCPCommunicator::getProtocol() const { return TransportNode::TCP; }

uint8 TCPCommunicator::getStatus() const { return status; }
    /*
    if (status == DISCONNECTED) return status;
    #ifdef WINDOWS
    LogService::fatalError("TCPCommunicator::getStatus() not implemented yet");
    return status;
    #else
    pollfd pfd;
    pfd.fd = (int) id;
    pfd.revents = 0;
    pfd.events = POLLOUT;

    if (poll(&pfd,1,0) > 0) {
        int error;
        socklen_t len = sizeof(error);
        getsockopt((int) id,SOL_SOCKET,SO_ERROR, (char*) &error,&len);
        if (error == 0) {
            if (status == CONNECTING) {
                const_cast<TCPCommunicator*>(this)->runConnected();
                return status;
            }
        } else if (status != DISCONNECTED) {
            const_cast<TCPCommunicator*>(this)->runDisconnected();
            return status;
        }
    }

    pfd.events = POLLIN | POLLHUP | POLLRDNORM;
    pfd.revents = 0;

    if (poll(&pfd, 1, 0) > 0) {
        char buffer;
        if (recv(pfd.fd, &buffer, sizeof(buffer), MSG_PEEK | MSG_DONTWAIT) == 0) {
               if (status != DISCONNECTED) const_cast<TCPCommunicator*>(this)->runDisconnected();
        } else if (status == CONNECTING) const_cast<TCPCommunicator*>(this)->runConnected();
    }

    return status;
    #endif
    */

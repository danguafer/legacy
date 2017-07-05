#include "UDPListener.h"
#include "UDPCommunicator.h"

#include "../Internet/IPV4Listener.h"
#include "../Internet/IPV6Listener.h"
#include "../Internet/IPV4Communicator.h"
#include "../Internet/IPV6Communicator.h"

#include <Veritas/etc/Socket/Socket.h>

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Net;
using namespace Transport;
using namespace Internet;

using Veritas::etc::Socket;

Socket::Address* getAddress(InternetNode *node, uint16 port) {
    switch (node->getProtocol()) {
        case InternetNode::IPV4: {
            IPV4Node* ipv4 = (IPV4Node*) node;
            return new Socket::Address(ipv4->getGroup(0), ipv4->getGroup(1), ipv4->getGroup(2), ipv4->getGroup(3), port);
        }
        case InternetNode::IPV6: {
            IPV6Node* ipv6 = (IPV6Node*) node;
            return new Socket::Address(ipv6->getGroup(0), ipv6->getGroup(1), ipv6->getGroup(2), ipv6->getGroup(3), ipv6->getGroup(4), ipv6->getGroup(5), ipv6->getGroup(6), ipv6->getGroup(7), port);
        }
        default: return 0;
    }
}

UDPListener::UDPListener(Internet::InternetListener *parent, UDPNode *node) : TransportListener(parent, node) {
    Socket *socket = new Socket(Socket::UDP);
    socket->blocking(false);

    Socket::Address *address = getAddress((InternetNode*) parent->getNode(), node->getPort());
    socket->bind(*address);
    delete address;

    id = (Handle) socket;

    islistening = true;
}

UDPListener::~UDPListener() {
    delete ((Socket*) id);
}

#include <iostream>
Communicator* UDPListener::accept() {
    Socket::Address incoming;
    Socket* socket = (Socket*) id;

    uint8 data[32];
    int32 recv = socket->recvfrom(data, 32, &incoming, true);
    if (recv > 0) {
        UDPCommunicator *c = 0;
        for (Communicators::iterator it = communicators.begin(); it != communicators.end() && !c; it++) {
            UDPCommunicator *cit = (UDPCommunicator*) *it;
            UDPNode *udpnode = (UDPNode*) cit->getNode();

            // it happens to be ipv4, so:
            IPV4Node *ipv4node = (IPV4Node*) cit->getParent()->getNode();
            if (udpnode->getPort() == incoming.getPort()
            &&  ipv4node->getGroup(0) == incoming.getGroup(0)
            &&  ipv4node->getGroup(2) == incoming.getGroup(1)
            &&  ipv4node->getGroup(2) == incoming.getGroup(2)
            &&  ipv4node->getGroup(3) == incoming.getGroup(3)) c = cit;
        }
        if (!c) {
            UDPNode *udpnode = new UDPNode(incoming.getPort());
            IPV4Node *ipv4node = new IPV4Node(incoming.getGroup(0), incoming.getGroup(1), incoming.getGroup(2), incoming.getGroup(3));
            IPV4Communicator *ipv4communicator = new IPV4Communicator(ipv4node);
            return new UDPCommunicator(ipv4communicator, udpnode);
        }
    }

    return 0;
}

uint8 UDPListener::getProtocol() const { return TransportNode::UDP; }

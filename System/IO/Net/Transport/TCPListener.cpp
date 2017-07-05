#include "TCPListener.h"
#include "TCPCommunicator.h"

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

Socket::Address* getAddress(InternetNode* node, uint16 port);

TCPListener::TCPListener(Internet::InternetListener *parent, TCPNode *node) : TransportListener(parent, node) {
    Socket *socket = new Socket(Socket::TCP);
    socket->blocking(false);
    socket->reuseAddress(true);

    Socket::Address *address = getAddress((InternetNode*) parent->getNode(), node->getPort());
    socket->bind(*address);
    delete address;

    socket->listen();
    id = (Handle) socket;

    islistening = true;
}

TCPListener::~TCPListener() { delete ((Socket*) id); }

Communicator* TCPListener::accept() {
    Socket *listener = (Socket*) id;
    Socket *client = listener->accept();

    if (client) {
        Socket::Address addr = client->getAddress();
        InternetCommunicator *internetCommunicator;
        switch (addr.getFamily()) {
            case Socket::Address::IPV4:
                internetCommunicator = new IPV4Communicator(new IPV4Node(addr.getGroup(0), addr.getGroup(1), addr.getGroup(2), addr.getGroup(3)));
            break;
            case Socket::Address::IPV6:
                internetCommunicator = new IPV6Communicator(new IPV6Node(addr.getGroup(0), addr.getGroup(1), addr.getGroup(2), addr.getGroup(3), addr.getGroup(4), addr.getGroup(5), addr.getGroup(6), addr.getGroup(7)));
            break;
        }

        return new TCPCommunicator((void*) client, internetCommunicator, new TCPNode(addr.getPort()));
    } else return 0;
}

uint8 TCPListener::getProtocol() const { return TransportNode::TCP; }

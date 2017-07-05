#include "TCPNode.h"

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Net;
using namespace Transport;

TCPNode::TCPNode(uint16 port) {
    this->port = port;
}

uint16 TCPNode::getPort() const { return port; }

uint8 TCPNode::getProtocol() const { return TCP; }

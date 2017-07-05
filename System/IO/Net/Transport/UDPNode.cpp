#include "UDPNode.h"

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Net;
using namespace Transport;

UDPNode::UDPNode(uint16 port) {
    this->port = port;
}

uint16 UDPNode::getPort() const { return port; }

uint8 UDPNode::getProtocol() const { return UDP; }

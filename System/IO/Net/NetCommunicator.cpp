#include "NetCommunicator.h"
#include "NetListener.h"

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Net;

NetCommunicator::NetCommunicator(NetCommunicator *parent, NetNode *node) : Communicator(node) { this->parent = parent; }
NetCommunicator::NetCommunicator(NetListener *listener, NetCommunicator *parent, NetNode *node) : Communicator(listener, node) {
    this->parent.manage(parent);
}

NetCommunicator::~NetCommunicator() {}

uint8 NetCommunicator::getCommunicatorType() const { return Node::NET; }

NetCommunicator* NetCommunicator::getParent() const { return parent; }

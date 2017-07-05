#include "NetListener.h"

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Net;

NetListener::NetListener(NetListener *parent, NetNode *node) : Listener(node) {
    this->parent = parent;
}
NetListener::~NetListener() {}

uint8 NetListener::getType() const { return Node::NET; }

NetListener* NetListener::getParent() const { return parent; }

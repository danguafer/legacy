#include "EthernetNode.h"

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Net;
using namespace Link;

EthernetNode::EthernetNode(uint8 a0, uint8 a1, uint8 a2, uint8 a3, uint8 a4, uint8 a5) {
    #define SET(X) addr[X] = a ## X
    SET(0);
    SET(1);
    SET(2);
    SET(3);
    SET(4);
    SET(5);
    #undef SET
}

uint8 EthernetNode::getProtocol() const { return ETHERNET; }

uint8 EthernetNode::getGroup(uint8 g) const { return addr[g]; }

#include "IPV4Node.h"

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Net;
using namespace Internet;

IPV4Node::IPV4Node(uint8 a0, uint8 a1, uint8 a2, uint8 a3) {
    #define SET(X) addr[X] = a ## X
    SET(0);
    SET(1);
    SET(2);
    SET(3);
    #undef SET
}

uint8 IPV4Node::getProtocol() const { return IPV4; }

uint8 IPV4Node::getGroup(uint8 g) const { return addr[g]; }

#include "../../../third-party/src/ssocket/ssocket.h"
#include <cstring>

IPV4Node::IPV4Node(void *saddr4) {
    sockaddr_in *addrin = (sockaddr_in*) saddr4;
    for (uint8 i = 0; i < 4; i++)
        addr[i] = addrin->sin_addr.s_addr >> (i*8);
}

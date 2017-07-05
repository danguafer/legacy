#include "IPV6Node.h"

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Net;
using namespace Internet;

IPV6Node::IPV6Node(uint16 a0, uint16 a1, uint16 a2, uint16 a3, uint16 a4, uint16 a5, uint16 a6, uint16 a7) {
    #define SET(X) addr[X] = a ## X
    SET(0);
    SET(1);
    SET(2);
    SET(3);
    SET(4);
    SET(5);
    SET(6);
    SET(7);
    #undef SET
}

uint16 IPV6Node::getGroup(uint8 g) const { return addr[g]; }

uint8 IPV6Node::getProtocol() const { return IPV6; }

#include "../../../third-party/src/ssocket/ssocket.h"
#include <cstring>

IPV6Node::IPV6Node(void *saddr6) {
    sockaddr_in6* addrin = (sockaddr_in6*) saddr6;
    for (uint8 i = 0; i < 8; i++)
        addr[i] = ADDRI6B(addrin, i*2) << 8 | ADDRI6B(addrin, i*2+1);
}

void* IPV6Node::createsockaddr(uint32 *length, uint16 port) {
    sockaddr_in6 *addrin = new sockaddr_in6;
    *length = sizeof(sockaddr_in6);
    memset(addrin, 0, sizeof(sockaddr_in6));

    addrin->sin6_family = AF_INET6;
    addrin->sin6_port = htons(port);
    for (uint8 i = 0; i < 8; i++) {
        ADDRI6B(addrin, i*2)   = addr[i] >> 8;
        ADDRI6B(addrin, i*2+1) = addr[i];
    }

    return addrin;
}

#include <Veritas/Definitions/Definitions.h>
#ifdef LINUX
#include "EthernetNode.h"

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Net;
using namespace Link;

#include "../../../third-party/src/ssocket/ssocket.h"
#include <cstring>

#include <linux/if_packet.h>

EthernetNode::EthernetNode(void *addrmac) {
    sockaddr_ll *addrll = (sockaddr_ll*) addrmac;
    for (uint8 i = 0; i < 6; i++)
        addr[i] = addrll->sll_addr[i];
}

void* EthernetNode::tosockaddr(void *addrmac) {
    sockaddr_ll *addrll = (sockaddr_ll*) addrmac;
    memset(addrll, 0, sizeof(sockaddr_ll));
    for (uint8 i = 0; i < 6; i++)
        addrll->sll_addr[i] = addr[i];

    return addrll;
}

#endif

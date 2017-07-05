#include <Veritas/Definitions/Definitions.h>
#ifdef WINDOWS
#include "EthernetNode.h"

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Net;
using namespace Link;

#include "../../../third-party/src/ssocket/ssocket.h"
#include <cstring>

EthernetNode::EthernetNode(void *addrmac) {
    uint8* src = (uint8*) addrmac;
    for (uint8 i = 0; i < 6; i++)
        addr[i] = src[i];
}

#endif

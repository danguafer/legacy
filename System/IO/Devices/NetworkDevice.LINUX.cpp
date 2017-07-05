#include <Veritas/Definitions/Definitions.h>
#ifdef LINUX
#include "NetworkDevice.h"
#include "../../IO/Net/Link/EthernetNode.h"
#include "../../IO/Net/Internet/IPV4Node.h"
#include "../../IO/Net/Internet/IPV6Node.h"

#include <sys/types.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <netpacket/packet.h>

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Devices;

using namespace IO;
using namespace Net;
using namespace Link;
using namespace Internet;

void NetworkDevice::systemCreateNetworkAdapter(const char *name) {
    ifaddrs* ifap = 0;
    getifaddrs(&ifap);

    for (ifaddrs* ifa = ifap; ifa; ifa = ifa->ifa_next) {
        switch (ifa->ifa_addr->sa_family) {
            case AF_INET: nodes.push_back(new IPV4Node(ifa->ifa_addr)); break;
            case AF_INET6: nodes.push_back(new IPV6Node(ifa->ifa_addr)); break;
            case AF_PACKET: nodes.push_back(new EthernetNode(ifa->ifa_addr)); break;
        }
    }

    freeifaddrs(ifap);
}

#endif

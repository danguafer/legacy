#define WINVER 0x0600

#include <Veritas/Definitions/Definitions.h>
#ifdef WINDOWS
#include "NetworkDevice.h"
#include "../../IO/Net/Link/EthernetNode.h"
#include "../../IO/Net/Internet/IPV4Node.h"
#include "../../IO/Net/Internet/IPV6Node.h"

#include <winsock2.h>
#include <iphlpapi.h>

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Devices;

using namespace IO;
using namespace Net;
using namespace Link;
using namespace Internet;

#include <cstdio>
#include <iostream>
void NetworkDevice::systemCreateNetworkAdapter(const char *name) {
    ULONG size = 1024*1024*32;
    IP_ADAPTER_ADDRESSES* list = (IP_ADAPTER_ADDRESSES*) new uint8[size];

    GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_INCLUDE_PREFIX, 0, list, &size);
    while (list) {
        for (PIP_ADAPTER_UNICAST_ADDRESS ua = list->FirstUnicastAddress; ua; ua = ua->Next)
            switch (ua->Address.lpSockaddr->sa_family) {
                case AF_INET: nodes.push_back(new IPV4Node(ua->Address.lpSockaddr)); break;
                case AF_INET6: nodes.push_back(new IPV6Node(ua->Address.lpSockaddr)); break;
            }
        nodes.push_back(new EthernetNode(list->PhysicalAddress));

        list = list->Next;
    }

    delete[] list;
}

#endif

#include "DomainNode.h"

#include <cstring>
#include <cstdlib>

#include "../../../third-party/src/ssocket/ssocket.h"

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Net;
using namespace Internet;

DomainNode::DomainNode(const char *name) {
    ipv4 = 0;
    ipv6 = 0;
    this->name = 0;

    this->name = (char*) realloc(this->name, strlen(name) + 1);
    strcpy((char*) this->name, name);

    if (!strcmp(name, "*")) {
        ipv4 = new IPV4Node(0, 0, 0, 0);
        ipv6 = new IPV6Node(0, 0, 0, 0, 0, 0, 0, 0);
    } else {
        addrinfo *list = 0, hints = {0};
        getaddrinfo(name, 0, 0, &list);
        for (addrinfo* ai = list; ai; ai = ai->ai_next) {
            if (ai->ai_family == AF_INET && ai->ai_protocol == 0) {
                if (ipv4) continue;
                sockaddr_in *addr = (sockaddr_in*) ai->ai_addr;
                #define GET(X) (addr->sin_addr.s_addr >> (X*8))
                ipv4 = new IPV4Node(GET(0), GET(1), GET(2), GET(3));
                #undef GET
            } else if (ai->ai_family == AF_INET6 && ai->ai_protocol == 0) {
                if (ipv6) continue;
                sockaddr_in6 *addr = (sockaddr_in6*) ai->ai_addr;
                #define GET(X) ADDRI6B(addr, X*2) << 8 | ADDRI6B(addr, X*2+1)
                ipv6 = new IPV6Node(GET(0), GET(1), GET(2), GET(3), GET(4), GET(5), GET(6), GET(7));
                #undef GET
            }
        }

        freeaddrinfo(list);
    }
}

DomainNode::~DomainNode() {
    delete ipv4;
    delete ipv6;
    delete[] name;
}

const char* DomainNode::getName() const { return name; }
IPV4Node* DomainNode::getIPV4Node() const { return ipv4; }
IPV6Node* DomainNode::getIPV6Node() const { return ipv6; }

uint8 DomainNode::getProtocol() const { return InternetNode::UNKNOWN; }

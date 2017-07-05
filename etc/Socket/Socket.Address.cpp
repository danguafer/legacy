#include "Socket.Address.h"

#include <Veritas/Definitions/Definitions.h>

#ifdef WINDOWS
    #include <winsock2.h>
    #include <ws2ipdef.h>
#else
    #include <netinet/ip.h>
    #include <cstring>
#endif

using Veritas::etc::Socket;

void Socket::Address::setFamily(FAMILY family) {
    if (this->family == family) return;

    this->family = family;
    if (nativeStruct) {
        free(nativeStruct);
        nativeStruct = 0;
        nativeStructSize = 0;
    }

    switch (family) {
        case IPV4: {
            sockaddr_in* addr = (sockaddr_in*) calloc(sizeof(sockaddr_in), 1);
            addr->sin_family = AF_INET;
            nativeStruct = addr;
            nativeStructSize = sizeof(sockaddr_in);
        } break;
        case IPV6: {
            sockaddr_in6* addr = (sockaddr_in6*) calloc(sizeof(sockaddr_in6), 1);
            addr->sin6_family = AF_INET6;
            nativeStruct = addr;
            nativeStructSize = sizeof(sockaddr_in6);
        } break;
        case ETHERNET: {
        } break;
    }
}

Socket::Address::Address() {
    this->family = UNKNOWN;
    nativeStruct = 0;
    nativeStructSize = 0;
}

Socket::Address::Address(FAMILY family) {
    this->family = UNKNOWN;
    nativeStruct = 0;
    nativeStructSize = 0;
    setFamily(family);
}

Socket::Address::Address(const Address &copy) {
    operator=(copy);
}

void Socket::Address::operator=(const Address &copy) {
    family = copy.family;
    nativeStructSize = copy.getNativeStructSize();
    nativeStruct = (uint8_t*) malloc(nativeStructSize);
    memcpy(nativeStruct, copy.nativeStruct, nativeStructSize);
}

Socket::Address::Address(const Address &copy, uint16_t port) {
    family = copy.family;
    nativeStructSize = copy.getNativeStructSize();
    nativeStruct = (uint8_t*) malloc(nativeStructSize);
    memcpy(nativeStruct, copy.nativeStruct, nativeStructSize);

    switch (family) {
        case IPV4:
            ((sockaddr_in*) nativeStruct)->sin_port = htons(port);
        break;
        case IPV6:
            ((sockaddr_in6*) nativeStruct)->sin6_port = htons(port);
        break;
    }
}



Socket::Address::Address(uint8_t IPv4a, uint8_t IPv4b, uint8_t IPv4c, uint8_t IPv4d, uint16_t port) {
    this->family = UNKNOWN;
    nativeStruct = 0;
    nativeStructSize = 0;

    setFamily(IPV4);
    sockaddr_in* addr = (sockaddr_in*) nativeStruct;
    ((char*) &addr->sin_addr)[0] = IPv4a;
    ((char*) &addr->sin_addr)[1] = IPv4b;
    ((char*) &addr->sin_addr)[2] = IPv4c;
    ((char*) &addr->sin_addr)[3] = IPv4d;
    addr->sin_port = htons(port);
}
Socket::Address::Address(uint16_t IPv6a, uint16_t IPv6b, uint16_t IPv6c, uint16_t IPv6d, uint16_t IPv6e, uint16_t IPv6f, uint16_t IPv6g, uint16_t IPv6h, uint16_t port) {
    this->family = UNKNOWN;
    nativeStruct = 0;
    nativeStructSize = 0;

    setFamily(IPV6);
    sockaddr_in6* addr = (sockaddr_in6*) nativeStruct;
    ((uint16_t*) &addr->sin6_addr)[0] = IPv6a;
    ((uint16_t*) &addr->sin6_addr)[1] = IPv6b;
    ((uint16_t*) &addr->sin6_addr)[2] = IPv6c;
    ((uint16_t*) &addr->sin6_addr)[3] = IPv6d;
    ((uint16_t*) &addr->sin6_addr)[4] = IPv6e;
    ((uint16_t*) &addr->sin6_addr)[5] = IPv6f;
    ((uint16_t*) &addr->sin6_addr)[6] = IPv6g;
    ((uint16_t*) &addr->sin6_addr)[7] = IPv6h;
    addr->sin6_port = htons(port);
}

Socket::Address::~Address() {
    free(nativeStruct);
}

Socket::Address::FAMILY Socket::Address::getFamily() const { return family; }

uint32_t Socket::Address::getNativeFamily() const {
    switch (getFamily()) {
        case Address::IPV4: return AF_INET;
        case Address::IPV6: return AF_INET6;
        case Address::ETHERNET: return UNKNOWN;
        case Address::UNKNOWN: return UNKNOWN;
    }
}

void* Socket::Address::getNativeStruct() const { return nativeStruct; }
uint32_t Socket::Address::getNativeStructSize() const { return nativeStructSize; }

uint16_t Socket::Address::getGroup(uint8_t group) const {
    switch (getFamily()) {
        case IPV4:
            if (group >= 4) return 0;
            return ((uint8_t*) &((sockaddr_in*) getNativeStruct())->sin_addr)[group];
        case IPV6:
            if (group >= 8) return 0;
            return ((uint16_t*) &((sockaddr_in6*) getNativeStruct())->sin6_addr)[group];
        default: // UNKNOWN
            return 0;
    }
}

uint16_t Socket::Address::getPort() const {
    switch (getFamily()) {
        case Address::IPV4: return ntohs(((sockaddr_in*) getNativeStruct())->sin_port);
        case Address::IPV6: return ntohs(((sockaddr_in6*) getNativeStruct())->sin6_port);
        default: // UNKNOWN
            return 0;
    }
}

std::ostream& operator<<(std::ostream& os, const Socket::Address& a) {
    os << a.getGroup(0) << '.'
       << a.getGroup(1) << '.'
       << a.getGroup(2) << '.'
       << a.getGroup(3) << ':'
       << a.getPort();
    return os;
}

bool Socket::Address::operator==(const Address& a) const {
    if (getFamily()   == UNKNOWN
    ||  a.getFamily() == UNKNOWN
    ||  getFamily()   != a.getFamily()
    ||  getPort()     != a.getPort()) return false;
    switch (getFamily()) {
        case IPV4: return getGroup(0) == a.getGroup(0)
                       && getGroup(1) == a.getGroup(1)
                       && getGroup(2) == a.getGroup(2)
                       && getGroup(3) == a.getGroup(3);

        case IPV6: return getGroup(0) == a.getGroup(0)
                       && getGroup(1) == a.getGroup(1)
                       && getGroup(2) == a.getGroup(2)
                       && getGroup(3) == a.getGroup(3)
                       && getGroup(4) == a.getGroup(4)
                       && getGroup(5) == a.getGroup(5)
                       && getGroup(6) == a.getGroup(6)
                       && getGroup(7) == a.getGroup(7);
    }
    return false;
}

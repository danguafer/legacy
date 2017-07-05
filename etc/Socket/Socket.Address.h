#pragma once

#include "Socket.h"
#include <cstdint>

namespace Veritas {
    namespace etc {
        class Socket::Address {
            public:
                enum FAMILY { UNKNOWN, ETHERNET, IPV4, IPV6 };
                Address();
                Address(FAMILY family);
                Address(uint8_t IPv4a, uint8_t IPv4b, uint8_t IPv4c, uint8_t IPv4d, uint16_t port);
                Address(uint16_t IPv6a, uint16_t IPv6b, uint16_t IPv6c, uint16_t IPv6d, uint16_t IPv6e, uint16_t IPv6f, uint16_t IPv6g, uint16_t IPv6h, uint16_t port);
                Address(const Address& copy);
                Address(const Address& copy, uint16_t port);
                ~Address();

                void operator=(const Address& a);
                bool operator==(const Address& a) const;

                uint16_t getGroup(uint8_t g) const;
                uint16_t getPort() const;

                FAMILY getFamily() const;
            private:
                void setFamily(FAMILY family);

                uint32_t getNativeFamily() const;
                void* getNativeStruct() const;
                uint32_t getNativeStructSize() const;

                friend class Socket;
                FAMILY family;
                void* nativeStruct;
                uint32_t nativeStructSize;
        };
    }
}

#include <ostream>
std::ostream& operator<<(std::ostream& os, const Veritas::etc::Socket::Address& address);

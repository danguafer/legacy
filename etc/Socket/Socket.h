#pragma once

#include <cstdint>

namespace Veritas {
    namespace etc {
        class Socket {
            public:
                class Address;
                enum PROTOCOL { UNKNOWN, TCP, UDP };

                Socket(PROTOCOL protocol);
                ~Socket();

                PROTOCOL getProtocol() const;

                bool listen();

                bool bind(const Address& address);
                bool connect(const Address& address);
                Address getAddress() const;

                Socket* accept();

                int32_t recv(void *data, uint32_t bytes, bool peek = false);
                int32_t send(const void *data, uint32_t bytes);

                int32_t recvfrom(void *data, uint32_t bytes, Address* origin, bool peek = false);
                int32_t sendto(const void *data, uint32_t bytes, const Address& target);

                uint32_t canRecv() const;
                uint32_t canSend() const;

                void blocking(bool b);
                bool isBlocking() const;

                void reuseAddress(bool b);
                bool isReusingAddress() const;

                int32_t getLastError() const;
            public:
                Socket(void *acceptedSocket, PROTOCOL protocol, const Address& address);
                void open(const Address& address);
                void close();

                uint32_t getNativeProtocol() const;
                void systemBlocking(bool b);

                void* id;
                bool isblocking, isreusingaddress;
                PROTOCOL protocol;
                Address* address;
        };
    }
}

#include "Socket.Address.h"

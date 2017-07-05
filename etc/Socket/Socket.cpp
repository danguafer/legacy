#include <Veritas/Definitions/Definitions.h>
#include "Socket.h"

#warning Organize definitions and check if both Windows and Linux are working

using namespace Veritas::etc;

#include <stdio.h>
#include <iostream>
#include <Veritas/etc/LogService/LogService.h>

#ifdef WINDOWS
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #include ioctl ioctlsocket
    #define close closesocket
#else
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <fcntl.h>
    #include <sys/ioctl.h>
    #include <unistd.h>

    #define INVALID_SOCKET (-1)
    #define SOCKET_ERROR (-1)
    #define SOCKET Handle
    #define WSAGetLastError(...) 0
#endif

Socket::Socket(PROTOCOL protocol) {
    id = 0;
    this->protocol = protocol;
    isblocking = true;

    #ifdef WINDOWS
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
        LogService::fatalError("WSAStartup failed with WSAGetLastError() = %d", WSAGetLastError());
    #endif
    address = 0;
}

Socket::Socket(void *acceptedSocket, PROTOCOL protocol, const Address &address) {
    id = acceptedSocket;
    this->protocol = protocol;
    isblocking = true;
    this->address = new Address();
    *this->address = address;
}

Socket::~Socket() {
    delete address;
    close();
    #ifdef WINDOWS
    WSACleanup();
    #endif
}

Socket::PROTOCOL Socket::getProtocol() const { return protocol; }

uint32_t Socket::getNativeProtocol() const {
    switch (getProtocol()) {
        case TCP: return SOCK_STREAM;
        case UDP: return SOCK_DGRAM;
    }
}

void Socket::open(const Address &address) {
    close();

    uint32_t family = address.getNativeFamily();
    uint32_t protocol = getNativeProtocol();

    //Create a socket
    if((id = (void*) socket(address.getNativeFamily(), getNativeProtocol(), 0 )) == (void*) INVALID_SOCKET)
        LogService::error("Socket creation failed with WSAGetLastError() = %d", WSAGetLastError());

    systemBlocking(isBlocking());
    reuseAddress(isReusingAddress());
}

bool Socket::bind(const Address &address) {
    open(address);

    if (!this->address) this->address = new Address;
    *this->address = address;

    if(::bind((SOCKET) id ,(struct sockaddr *) address.getNativeStruct(), address.getNativeStructSize()) == SOCKET_ERROR) {
        LogService::error("Bind failed with WSAGetLastError() = %d", WSAGetLastError());
        return false;
    }
    return true;
}

bool Socket::connect(const Address &address) {
    open(address);

    if (!this->address) this->address = new Address;
    *this->address = address;
    ::connect((SOCKET) id, (sockaddr*) address.getNativeStruct(), address.getNativeStructSize());
    /*
    if (::connect((SOCKET) id, (sockaddr*) address.getNativeStruct(), address.getNativeStructSize()) == SOCKET_ERROR) {
        LogService::error("Connect failed with WSAGetLastError() = %d", WSAGetLastError());
        return false;
    }
    */
    return true;
}

bool Socket::listen() { return ::listen((SOCKET) id, SOMAXCONN) >= 0; }

Socket* Socket::accept() {
    Socket::Address incoming(getAddress().getFamily());
    socklen_t len = incoming.getNativeStructSize();
    SOCKET acceptedSocket = ::accept((SOCKET) id, (sockaddr*) incoming.getNativeStruct(), &len);

    if (acceptedSocket != INVALID_SOCKET) {
        Socket *socket = new Socket((void*) acceptedSocket, getProtocol(), incoming);
        socket->blocking(isBlocking());
        return socket;
    } else return 0;
}

void Socket::close() {
    if (id) ::close((SOCKET) id);
    id = 0;
}

uint32_t Socket::canRecv() const {
    long unsigned int count;
    if (ioctl((SOCKET) id, FIONREAD, &count) < 0) return 0;
    return count;
}

uint32_t Socket::canSend() const {
    uint32_t sendbuff;
    socklen_t optlen = sizeof(sendbuff);
    getsockopt((SOCKET) id, SOL_SOCKET, SO_SNDBUF, (char*) &sendbuff, &optlen);
    return sendbuff;
}

int32_t Socket::getLastError() const { return errno; }

int32_t Socket::recv(void *data, uint32_t bytes, bool peek) { return ::recv((SOCKET) id, (char*) data, bytes, peek ? MSG_PEEK : 0); }
int32_t Socket::send(const void *data, uint32_t bytes) { return ::send((SOCKET) id, (char*) data, bytes, 0); }

int32_t Socket::recvfrom(void *data, uint32_t bytes, Address *origin, bool peek) {
    origin->setFamily(getAddress().getFamily());
    socklen_t slen = origin->getNativeStructSize();
    return ::recvfrom((SOCKET) id, (char*) data, bytes, peek ? MSG_PEEK : 0, (sockaddr*) origin->getNativeStruct(), &slen);
}

int32_t Socket::sendto(const void *data, uint32_t bytes, const Address& target) {
    return ::sendto((SOCKET) id, (char*) data, bytes, 0, (sockaddr*) target.getNativeStruct(), target.getNativeStructSize());
}

void Socket::blocking(bool b) {
    isblocking = b;
    if (id) systemBlocking(b);
}

void Socket::systemBlocking(bool b) {
    #ifdef __unix
    int flags = fcntl((SOCKET) id, F_GETFL, 0);
    if (b) flags &= ~O_NONBLOCK;
    else   flags |=  O_NONBLOCK;
    if (fcntl((SOCKET) id, F_SETFL, flags) < 0) perror("Socket non-blocking");
    #else
    u_long iMode = !b;
    if (ioctlsocket((SOCKET) id, FIONBIO, &iMode) == SOCKET_ERROR) {
        LogService::error("WSAGetLastError = %d", WSAGetLastError());
    }
    #endif
}

bool Socket::isBlocking() const { return isblocking; }

Socket::Address Socket::getAddress() const { return address ? *address : Address(); }

void Socket::reuseAddress(bool b) {
    isreusingaddress = b;
    if (id) {
        int on = b;
        if (setsockopt((SOCKET) id, SOL_SOCKET, SO_REUSEADDR, (char *) &on, sizeof(on)) < 0) {
            perror("setsockopt(SO_REUSEADDR) failed");
        }
    }
}

bool Socket::isReusingAddress() const { return isreusingaddress; }

#pragma once

#if defined(_WIN32) || defined(_WIN64)
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #include <windows.h>
    #define SHUT_RDWR SD_BOTH
    #ifndef EWOULDBLOCK
        #define EWOULDBLOCK WSAEWOULDBLOCK
    #endif
    #ifndef EINTR
        #define EINTR WSAEINTR
    #endif
    #ifndef EAGAIN
        #define EAGAIN WSAEWOULDBLOCK
    #endif
    #define ioctl ioctlsocket
    #define ADDRI6B(ADDR, X) ADDR->sin6_addr.u.Byte[X]
#else
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <sys/ioctl.h>
    #include <netdb.h>
    #include <errno.h>
    #include <unistd.h>
    #include <poll.h>
    #include <fcntl.h>
    #include <stdio.h>
    #define ADDRI6B(ADDR, X) ((char*) &ADDR->sin6_addr)[X]
#endif

#ifndef MSG_NOSIGNAL
    #define MSG_NOSIGNAL 0
#endif

#ifdef __cplusplus
extern "C" {
#endif

int ssocket(int domain, int type, int protocol);
void ssocket_nonblock(int socket);
int sclose(int socket);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
// not implemented
class SocketWrapper {
    public:
        SocketWrapper(int domain, int type, int protocol);
        ~SocketWrapper();

        void setNonblock();
    private:
};
#endif

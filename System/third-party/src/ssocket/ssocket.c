#include "ssocket.h"

#if defined(_WIN32) || defined(_WIN64)
static struct WSAData wsadata;
static unsigned int i = 0;
#endif

int ssocket(int domain, int type, int protocol) {
    #if defined(_WIN32) || defined(_WIN64)
    if (i++ == 0) WSAStartup(0x202, &wsadata);
    #endif

    return socket(domain, type, protocol);
}

int sclose(int socket) {
    shutdown(socket, SHUT_RDWR);
    close(socket);

    #if defined(_WIN32) || defined(_WIN64)
    if (--i == 0) WSACleanup();
    #endif
}

void ssocket_nonblock(int socket) {
    #ifdef __unix
    if (fcntl(socket, F_SETFL, fcntl(socket, F_GETFL, 0) | O_NONBLOCK) < 0) perror("Socket non-blocking");
    #else
    u_long iMode = 1;
    ioctl(socket, FIONBIO, &iMode);
    #endif
}

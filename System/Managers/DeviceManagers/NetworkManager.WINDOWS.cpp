#include "NetworkManager.h"

using namespace Silexars;
using namespace System;
using namespace Managers;
using namespace DeviceManagers;

using namespace IO;
using namespace Devices;

#include <Veritas/Definitions/Definitions.h>
#ifdef WINDOWS
#include "NetworkManager.h"
#include <windows.h>

void NetworkManager::systemCreateNetworkManager() {
    WSAData wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
}
void NetworkManager::systemDestroyNetworkManager() {
    WSACleanup();
}

#else

void NetworkManager::systemCreateNetworkManager() {}
void NetworkManager::systemDestroyNetworkManager() {}

#endif

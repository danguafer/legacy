#include "NetworkManager.h"

using namespace Silexars;
using namespace System;
using namespace Managers;
using namespace DeviceManagers;

using namespace IO;
using namespace Devices;

NetworkManager::NetworkManager() {
    systemCreateNetworkManager();
    devices.push_back(new NetworkDevice("Virtual Network Adapter"));
}
NetworkManager::~NetworkManager() {
    iterate(List, &devices) delete *iterator;
    systemDestroyNetworkManager();
}

NetworkManager::iterator NetworkManager::begin() { return devices.begin(); }
NetworkManager::iterator NetworkManager::end() { return devices.end(); }
uint32 NetworkManager::size() const { return devices.size(); }

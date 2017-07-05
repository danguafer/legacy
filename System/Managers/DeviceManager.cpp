//!Complete

#include "DeviceManager.h"

using namespace Silexars;
using namespace System;
using namespace Managers;
using namespace DeviceManagers;

DeviceManager::DeviceManager() {  }
DeviceManager::~DeviceManager() {  }

GraphicsManager* DeviceManager::getDisplayManager() const { return &const_cast<DeviceManager*>(this)->displayManager; }
NetworkManager* DeviceManager::getNetworkManager() const { return &const_cast<DeviceManager*>(this)->networkManager; }
SensorManager* DeviceManager::getSensorManager() const { return &const_cast<DeviceManager*>(this)->sensorManager; }

void DeviceManager::manage() {
    displayManager.manage();
    //networkManager.manage();
    sensorManager.manage();
}

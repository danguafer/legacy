//!Complete

#include "GraphicsManager.h"

using namespace Silexars;
using namespace System;
using namespace Managers;
using namespace DeviceManagers;

using namespace IO;
using namespace Devices;

GraphicsManager::GraphicsManager() { devices.push_back(new GraphicsDevice("Virtual Graphics Device")); }
GraphicsManager::~GraphicsManager() {
    iterate(GraphicsManager,this) delete *iterator;
}

GraphicsManager::iterator GraphicsManager::begin() { return devices.begin(); }
GraphicsManager::iterator GraphicsManager::end() { return devices.end(); }
uint32 GraphicsManager::size() const { return devices.size(); }

void GraphicsManager::manage() {}

GraphicsDevice* GraphicsManager::getDefaultDisplay() const {
    if (size()) return (GraphicsDevice*) *const_cast<GraphicsManager*>(this)->begin();
    else return 0;
}

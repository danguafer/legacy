//!Complete

#include "GraphicsDevice.h"

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Devices;
using namespace Displays;

GraphicsDevice::GraphicsDevice(const char *name) : Device(name) {
    systemCreateDisplay(name,type);
}

GraphicsDevice::~GraphicsDevice() {
    systemDestroyDisplay();
    iterate(GraphicsDevice,this) delete *iterator;
}

GraphicsDevice::iterator GraphicsDevice::begin() { return displays.begin(); }
GraphicsDevice::iterator GraphicsDevice::end() { return displays.end(); }
uint32 GraphicsDevice::size() const { return displays.size(); }

Screen* GraphicsDevice::getDefaultScreen() const {
    if (size()) return *displays.begin();
    else return 0;
}

uint8 GraphicsDevice::getDeviceType() const { return DISPLAY; }

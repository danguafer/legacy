#include "NetworkDevice.h"

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Devices;

NetworkDevice::NetworkDevice(const char* name) : Device(name) { systemCreateNetworkAdapter(name); }
NetworkDevice::~NetworkDevice() { iterate(List, &nodes) delete *iterator; }

NetworkDevice::iterator NetworkDevice::begin() { return nodes.begin(); }
NetworkDevice::iterator NetworkDevice::end() { return nodes.end(); }
uint32 NetworkDevice::size() const { return nodes.size(); }

uint8 NetworkDevice::getDeviceType() const { return NETWORK; }

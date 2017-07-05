//!Complete

#include "Device.h"

#include <cstring>

using namespace Silexars::System::IO::Devices;

Device::Device(const char *name) : Communicator(0) {
    id = 0;
    strncpy(this->name, name, sizeof(this->name) - 1); this->name[sizeof(this->name) - 1] = 0;
}
Device::~Device() {}

const char* Device::getName() const { return name; }

uint8 Device::getCommunicatorType() const { return Node::DEVICE; }

uint8 Device::getStatus() const { return CONNECTED; }

uint32 Device::write(const void *data, uint32 size) { return 0; }
uint32 Device::read(void *data, uint32 size) { return 0; }
uint32 Device::peek(void *data, uint32 size) const { return 0; }

uint32 Device::canWrite() const { return 0; }
uint32 Device::canRead() const { return 0; }

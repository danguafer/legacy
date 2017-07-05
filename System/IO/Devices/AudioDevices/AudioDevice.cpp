//!Complete

#include "AudioDevice.h"

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Devices;
using namespace AudioDevices;

AudioDevice::AudioDevice(uint8 type, uint8 channels, uint8 format, uint32 fps) : Device("Virtual Audio Device") {
    this->type = type;
    this->channels = channels;
    this->format = format;
    this->fps = fps;
}
AudioDevice::~AudioDevice() {}

uint8 AudioDevice::getDeviceType() const { return type; }
uint8 AudioDevice::getChannels() const { return channels; }
uint8 AudioDevice::getFormat() const { return format; }
uint32 AudioDevice::getFPS() const { return fps; }

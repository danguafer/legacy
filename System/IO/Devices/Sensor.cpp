#include "Sensor.h"

using namespace Silexars::System;
using namespace IO::Devices;
using namespace Managers::DeviceManagers;

Sensor::Sensor(SensorManager* sensorManager, uint8 sensorType) : Device("Sensor") {
    isenabled = false;
    systemCSensor(sensorManager, sensorType);
}
Sensor::~Sensor() {
    if (isEnabled()) disable();
    systemDSensor();
}

void Sensor::enable() {
    systemEnable();
    isenabled = true;
}
void Sensor::disable() {
    systemDisable();
    isenabled = false;
}
bool Sensor::isEnabled() const { return isenabled; }

uint8 Sensor::getDeviceType() const { return SENSOR; }

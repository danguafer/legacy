#include <Veritas/Definitions/Definitions.h>
#ifdef LINUX
#include "Sensor.h"
#include "../../Managers/DeviceManagers/SensorManager.h"

using namespace Silexars::System;
using namespace IO::Devices;
using namespace Managers::DeviceManagers;

void Sensor::systemCSensor(SensorManager *sensorManager, uint8 sensorType) {}
void Sensor::systemDSensor() {}
void Sensor::systemEnable() {}
void Sensor::systemDisable() {}

#endif

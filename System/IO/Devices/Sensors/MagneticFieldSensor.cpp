#include "MagneticFieldSensor.h"

using namespace Silexars;
using namespace Math;
using namespace System;
using namespace IO::Devices::Sensors;
using namespace Managers::DeviceManagers;

MagneticFieldSensor::MagneticFieldSensor(SensorManager* sensorManager) : Sensor(sensorManager, MAGNETIC_FIELD_SENSOR) {
    vector = vec3(0.0f);
}
MagneticFieldSensor::~MagneticFieldSensor() {}

vec3 MagneticFieldSensor::getVector() const { return vector; }

#include "RotationSensor.h"

using namespace Silexars;
using namespace Math;
using namespace System;
using namespace IO::Devices::Sensors;
using namespace Managers::DeviceManagers;

RotationSensor::RotationSensor(SensorManager* sensorManager) : Sensor(sensorManager, ROTATION_SENSOR) {
    vector = vec3(0.0f);
}
RotationSensor::~RotationSensor() {}

vec3 RotationSensor::getVector() const { return vector; }

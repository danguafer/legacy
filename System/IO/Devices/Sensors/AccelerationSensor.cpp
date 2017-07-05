#include "AccelerationSensor.h"

using namespace Silexars;
using namespace Math;
using namespace System;
using namespace IO::Devices::Sensors;
using namespace Managers::DeviceManagers;

AccelerationSensor::AccelerationSensor(SensorManager* sensorManager) : Sensor(sensorManager, ACCELERATION_SENSOR) {
    vector = vec3(0.0f);
}
AccelerationSensor::~AccelerationSensor() {}

vec3 AccelerationSensor::getVector() const { return vector; }

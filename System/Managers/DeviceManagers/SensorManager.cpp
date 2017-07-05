#include "SensorManager.h"

using namespace Silexars::System;
using namespace IO::Devices;
using namespace Sensors;
using namespace Managers::DeviceManagers;

SensorManager::SensorManager() {
    accelerationSensor = 0;
    systemCSensorManager();

    orientationSensor = new RotationSensor(this);
    accelerationSensor = new AccelerationSensor(this);
    magneticFieldSensor = new MagneticFieldSensor(this);
}

SensorManager::~SensorManager() {
    delete orientationSensor;
    delete accelerationSensor;
    delete magneticFieldSensor;
    systemDSensorManager();
}

void SensorManager::manage() { systemManage(); }

AccelerationSensor* SensorManager::getDefaultAccelerationSensor() const {
    if (!accelerationSensor->isEnabled()) accelerationSensor->enable();
    return accelerationSensor;
}

RotationSensor* SensorManager::getDefaultRotationSensor() const {
    if (!orientationSensor->isEnabled()) orientationSensor->enable();
    return orientationSensor;
}

MagneticFieldSensor* SensorManager::getDefaultMagneticFieldSensor() const {
    if (!magneticFieldSensor->isEnabled()) magneticFieldSensor->enable();
    return magneticFieldSensor;
}

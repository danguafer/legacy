#include <Veritas/Definitions/Definitions.h>
#ifdef ANDROID
#include "Sensor.h"
#include "../../Managers/DeviceManagers/SensorManager.h"
#include <android/sensor.h>
#include <android/log.h>

using namespace Silexars::System;
using namespace IO::Devices;
using namespace Managers::DeviceManagers;

struct NativeSensorManager {
    ASensorEventQueue* queue;
    ASensorManager* sensorManager;
    ALooper* looper;
};

struct NativeSensor { // must match declaration on Sensor.ANDROID.cpp
    NativeSensorManager* nsm;
    const ASensor *sensor;
};

void Sensor::systemCSensor(SensorManager *sensorManager, uint8 sensorType) {
    uint32 nativeSensorType;
    switch (sensorType) {
        case ACCELERATION_SENSOR: nativeSensorType = ASENSOR_TYPE_ACCELEROMETER; break;
        case ROTATION_SENSOR: nativeSensorType = ASENSOR_TYPE_GYROSCOPE; break;
        case MAGNETIC_FIELD_SENSOR: nativeSensorType = ASENSOR_TYPE_MAGNETIC_FIELD; break;
    }

    NativeSensor* ns = new NativeSensor;
    ns->nsm = (NativeSensorManager*) sensorManager->id;
    ns->sensor = ASensorManager_getDefaultSensor(ns->nsm->sensorManager, nativeSensorType);
    id = (Handle) ns;
}

void Sensor::systemDSensor() {
    NativeSensor* ns = (NativeSensor*) id;
    delete ns;
}

void Sensor::systemEnable() {
    NativeSensor* ns = (NativeSensor*) id;
    if (ns->sensor) {
        ASensorEventQueue_enableSensor(ns->nsm->queue, ns->sensor);
        ASensorEventQueue_setEventRate(ns->nsm->queue, ns->sensor, (1000L/60)*1000);
    }
}

void Sensor::systemDisable() {
    NativeSensor* ns = (NativeSensor*) id;
    if (ns->sensor) ASensorEventQueue_disableSensor(ns->nsm->queue, ns->sensor);
}

#endif

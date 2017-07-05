#include <Veritas/Definitions/Definitions.h>
#ifdef ANDROID
#include "SensorManager.h"

#include <android/sensor.h>
#include <android/looper.h>

using namespace Silexars;
using namespace System::Managers::DeviceManagers;
using namespace Math;

struct NativeSensorManager {
    ASensorEventQueue* queue;
    ASensorManager* sensorManager;
    ALooper* looper;
};

int SensorManager::acallback(int fd, int events, void *data) {
    SensorManager* sm = (SensorManager*) data;
    NativeSensorManager* nsm = (NativeSensorManager*) sm->id;
    ASensorEvent event;

    while (ASensorEventQueue_getEvents(nsm->queue, &event, 1) > 0) {
        switch (event.type) {
            case ASENSOR_TYPE_ACCELEROMETER: sm->accelerationSensor->vector = vec3(event.acceleration.x, event.acceleration.y, event.acceleration.z); break;
            case ASENSOR_TYPE_GYROSCOPE: sm->orientationSensor->vector = vec3(event.vector.x, event.vector.y, event.vector.z); break;
            case ASENSOR_TYPE_MAGNETIC_FIELD: sm->magneticFieldSensor->vector = vec3(event.magnetic.x, event.magnetic.y, event.magnetic.z);
        }
    }

    return 1;
}

void SensorManager::systemCSensorManager() {
    NativeSensorManager* nsm = new NativeSensorManager();
    nsm->sensorManager = ASensorManager_getInstance();
    nsm->looper = ALooper_prepare(0);
    nsm->queue = ASensorManager_createEventQueue(nsm->sensorManager, nsm->looper, 3, acallback, this);
    id = (Handle) nsm;
}

void SensorManager::systemDSensorManager() {
    NativeSensorManager* nsm = (NativeSensorManager*) id;
    ASensorManager_destroyEventQueue(nsm->sensorManager, nsm->queue);
    ALooper_release(nsm->looper);
    delete nsm;
}

void SensorManager::systemManage() {}

#endif

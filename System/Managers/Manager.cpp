//!Complete

#include "Manager.h"

using namespace Silexars;
using namespace System;
using namespace Managers;

Manager::Manager() {}
Manager::~Manager() {}

Manager* Manager::getManager() {
    static Manager* manager = 0;

    if (!manager) manager = new Manager();
    return manager;
}

WindowManager* Manager::getWindowManager() const { return &const_cast<Manager*>(this)->windowManager; }
DeviceManager* Manager::getDeviceManager() const { return &const_cast<Manager*>(this)->deviceManager; }
ProcessManager* Manager::getProcessManager() const { return &const_cast<Manager*>(this)->processManager; }

void Manager::manage() {
    deviceManager.manage();
    processManager.manage();
    windowManager.manage();
}

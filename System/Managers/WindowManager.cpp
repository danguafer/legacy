//!Complete

#include "WindowManager.h"

using namespace Silexars;
using namespace System;
using namespace Managers;
using namespace DeviceManagers;

using namespace IO;
using namespace Devices;
using namespace UI;

WindowManager::WindowManager() {}
WindowManager::~WindowManager() {}

WindowManager::iterator WindowManager::begin() { return windows.begin(); }
WindowManager::iterator WindowManager::end() { return windows.end(); }
uint32 WindowManager::size() const { return windows.size(); }

void WindowManager::manage() {
    for (iterator iterator = begin(); iterator != end();) {
        Window* w = *iterator; iterator++;
        w->manage();
    }
}

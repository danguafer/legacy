//!Complete

#include <Veritas/Definitions/Definitions.h>
#ifdef WINDOWS

#include <windows.h>

#include "GraphicsDevice.h"
#include "Displays/Screen.h"

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Devices;
using Devices::GraphicsDevice;
using Displays::Screen;

void GraphicsDevice::systemCreateDisplay(const char *name, uint8 type) {
    DISPLAY_DEVICE dd;
    dd.cb = sizeof(DISPLAY_DEVICE);

    for (DWORD i = 0; EnumDisplayDevices(0, i, &dd, 0); i++) {
        if (dd.StateFlags & DISPLAY_DEVICE_ACTIVE) {
            DISPLAY_DEVICE dd2 = {0};
            dd2.cb = sizeof(DISPLAY_DEVICE);
            for (DWORD j = 0; EnumDisplayDevices(dd.DeviceName, j, &dd2, 0); j++) {
                Screen *screen = new Screen(this, i);
                strncpy(screen->name,dd2.DeviceString,sizeof(screen->name)-1); screen->name[sizeof(screen->name)-1] = 0;
                screen->id = (Handle) CreateDC("DISPLAY", screen->name, NULL, NULL);
                displays.push_back(screen);
            }
        }
    }
}

void GraphicsDevice::systemDestroyDisplay() {}

#endif

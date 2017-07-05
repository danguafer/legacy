//!Complete

#include <Veritas/Definitions/Definitions.h>
#ifdef LINUX

#include <X11/Xlib.h>

#include "GraphicsDevice.h"
#include "Displays/Screen.h"

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Devices;
using Displays::Screen;

void GraphicsDevice::systemCreateDisplay(const char *name, uint8 type) {
    if ((id = (Handle) XOpenDisplay(0))) {
        int32 count = XScreenCount((::Display*) id);
        for (int32 i = 0; i < count; i++)
            displays.push_back(new Displays::Screen(this,i));
    }
}

void GraphicsDevice::systemDestroyDisplay() { if (id) XCloseDisplay((::Display*) id); }

#endif

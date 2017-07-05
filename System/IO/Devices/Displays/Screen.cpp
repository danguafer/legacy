//!Complete

#include "Screen.h"
#include "../GraphicsDevice.h"

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Devices;
using namespace Displays;

Screen::Screen(GraphicsDevice *display, uint8 i) : Display(display->getName()) {
    this->i = i;
    this->parent = display;
    systemCreateScreen(display,i);
}

uint8 Screen::getDeviceType() const { return SCREEN; }

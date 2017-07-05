//!Complete

#include <Veritas/Definitions/Definitions.h>
#ifdef LINUX

#include <X11/Xlib.h>

#include "Screen.h"
#include "../GraphicsDevice.h"

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Devices;
using namespace Displays;

using Displays::Screen;

#include <cstring>
#include <cstdio>

void Screen::systemCreateScreen(GraphicsDevice *display, uint8 i) {
    sprintf(&name[strlen(name)],":%d",i);
    id = (Handle) ScreenOfDisplay(display->id,i);
}

Screen::~Screen() {}

uint32 Screen::getWidth() const { return XWidthOfScreen((::Screen*) id); }
uint32 Screen::getHeight() const { return XHeightOfScreen((::Screen*) id); }
uint8 Screen::getIndex() const { return i; }

#endif

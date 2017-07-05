//!Complete

#include <Veritas/Definitions/Definitions.h>
#ifdef WINDOWS

#include <windows.h>

#include "Screen.h"

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Devices;
using namespace Displays;

using Displays::Screen;

void Screen::systemCreateScreen(GraphicsDevice *display, uint8 i) {}

Screen::~Screen() { DeleteDC((HDC) id); }

uint32 Screen::getWidth() const { return GetDeviceCaps((HDC) id, HORZRES); }
uint32 Screen::getHeight() const { return GetDeviceCaps((HDC) id, VERTRES); }
uint8 Screen::getIndex() const { return i; }

#endif

#include <Veritas/Definitions/Definitions.h>
#ifdef ANDROID
#include "Keyboard.h"

using namespace Silexars::System;
using namespace IO::Devices;

uint8 Keyboard::translationTable[256];

void Keyboard::press(uint32 keyCode) {}
void Keyboard::release(uint32 keyCode) {}

#endif

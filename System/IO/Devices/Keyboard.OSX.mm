#include <Silexars/Definitions/Definitions.h>
#ifdef OSX
#include "Keyboard.h"

using namespace Silexars::System::IO::Devices;
uint8 Keyboard::translationTable[256];
void Keyboard::press(uint32 keyCode) {}
void Keyboard::release(uint32 keyCode) {}

#endif

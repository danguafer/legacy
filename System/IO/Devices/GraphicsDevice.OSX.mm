#include <Silexars/Definitions/Definitions.h>
#ifdef OSX
#include "GraphicsDevice.h"

using namespace Silexars::System::IO::Devices;

void GraphicsDevice::systemCreateDisplay(const char *name, uint8 type) {}
void GraphicsDevice::systemDestroyDisplay() {}

#endif

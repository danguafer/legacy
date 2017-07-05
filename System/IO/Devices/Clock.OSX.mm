#include <Silexars/Definitions/Definitions.h>
#ifdef OSX
#include "Clock.h"

using namespace Silexars::System::IO::Devices;

uint64 Clock::getTime() { return 0; }

#endif

//!Clean

#ifndef SILEXARS_MANAGEMENT_DEVICES_AUDIODEVICES_DEFINITIONS_H_
#define SILEXARS_MANAGEMENT_DEVICES_AUDIODEVICES_DEFINITIONS_H_

#include "../../Definitions/Definitions.h"

#if defined(WINDOWS) || defined(EMSCRIPTEN) || defined(APPLE) || defined(LINUX)
    #define OPENAL
#elif defined(ANDROID)
    #define OPENSLES
#endif

#endif

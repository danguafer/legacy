//!Complete

#include <Veritas/Definitions/Definitions.h>
#ifdef WINDOWS
#include "Clock.h"

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Devices;

#include <windows.h>
#include <ctime>

uint64 Clock::getTime() { return getTime(1000); }

uint64 Clock::getTime(uint64 precision) {
    LARGE_INTEGER c,f;
    QueryPerformanceFrequency(&f);
    QueryPerformanceCounter(&c);
    return c.QuadPart*precision/f.QuadPart;
}

int8 Clock::getTimezone() {
    TIME_ZONE_INFORMATION tzi;
    GetTimeZoneInformation(&tzi);
    return -tzi.Bias/60;
}

#endif

//!Complete
#include <Veritas/Definitions/Definitions.h>
#ifdef UNIX
#include "Clock.h"

#include <sys/time.h>
#include <ctime>

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Devices;

uint64 Clock::getTime() {
    timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return t.tv_sec*1000 + t.tv_nsec/1000000;
}

uint64 Clock::getTime(uint64 precision) {
    timespec t;
    clock_gettime(CLOCK_MONOTONIC,&t);
    return ((uint64) t.tv_sec)*precision + (((uint64) t.tv_nsec)*precision)/1000000000L;
}

int8 Clock::getTimezone() {
    time_t t0 = time(0);
    tm *t = localtime(&t0);
    return t->tm_gmtoff;
}

#endif

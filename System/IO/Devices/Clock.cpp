//!Complete

#include "Clock.h"

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Devices;

#include <ctime>

uint32 Clock::getYear() {
    time_t t0 = time(0);
    tm *t = localtime(&t0);
    return t->tm_year;
}
uint8 Clock::getMonth() {
    time_t t0 = time(0);
    tm *t = localtime(&t0);
    return t->tm_mon;
}
uint8 Clock::getDay() {
    time_t t0 = time(0);
    tm *t = localtime(&t0);
    return t->tm_mday;
}
uint8 Clock::getHours() {
    time_t t0 = time(0);
    tm *t = localtime(&t0);
    return t->tm_hour;
}
uint8 Clock::getMinutes() {
    time_t t0 = time(0);
    tm *t = localtime(&t0);
    return t->tm_min;
}
uint8 Clock::getSeconds() {
    time_t t0 = time(0);
    tm *t = localtime(&t0);
    return t->tm_sec;
}

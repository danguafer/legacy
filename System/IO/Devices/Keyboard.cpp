//!Complete

#include "Keyboard.h"

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Devices;

bool Keyboard::pressmap[256] = { 0 };

void Keyboard::hit(uint32 keyCode) {
    press(keyCode);
    release(keyCode);
}

uint32 Keyboard::systemToKey(uint32 system) { return translationTable[system]; }
uint32 Keyboard::keyToSystem(uint32 key) {
    // use inverse table instead?
    for (uint32 i = 0; i < 256; i++)
        if (translationTable[i] == key)
            return i;
    return 0;
}

bool Keyboard::isPressed(uint32 keyCode) { return pressmap[keyCode]; }

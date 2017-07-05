#include "Touchscreen.Touch.h"
#include "Clock.h"

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Devices;
using namespace Math;

Touchscreen::Touch::Touch(vec2 position, uint8 id, bool ishovering) {
    this->id = id;
    this->position = position;
    this->ishovering = ishovering;
    Touchscreen::touches.push_back(this);
}

Touchscreen::Touch::~Touch() { Touchscreen::touches.remove(this); }

vec2 Touchscreen::Touch::getPosition() const { return position; }
bool Touchscreen::Touch::isHovering() const { return ishovering; }

void Touchscreen::Touch::start(vec2 position) {
    initialTime = previousTime = time = Clock::getTime();
    initialPosition = previousPosition = this->position = position;
}

void Touchscreen::Touch::move(vec2 position) {
    previousPosition = this->position;
    this->position = position;

    previousTime = time;
    time = Clock::getTime();
}

uint8 Touchscreen::Touch::getID() const { return id; }

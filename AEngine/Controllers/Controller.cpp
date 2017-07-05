#include "Controller.h"

using namespace Silexars;
using namespace AEngine;
using namespace Controllers;
using namespace Cinema;

using namespace System::IO::Devices;
using namespace Math;

Controller::Controller(CinemaObject *object) {
    rx = ry = 0.0f;
    attach(object);
}

void Controller::attach(CinemaObject *object) {
    this->object = object;
}

void Controller::control(uint32 udt) {
    float32 dt = udt/1000.0f;

    ry += (Keyboard::isPressed(Keyboard::RIGHT) - Keyboard::isPressed(Keyboard::LEFT))*dt;
    rx += (Keyboard::isPressed(Keyboard::UP) - Keyboard::isPressed(Keyboard::DOWN))*dt;
    rx = clamp(rx, -PI/2, PI/2);

    vec3 direction = vec3(Keyboard::isPressed(Keyboard::D) - Keyboard::isPressed(Keyboard::A), 0.0f, Keyboard::isPressed(Keyboard::S) - Keyboard::isPressed(Keyboard::W));
    vec3 vertical = vec3(0.0f, Keyboard::isPressed(Keyboard::SPACEBAR) - Keyboard::isPressed(Keyboard::LCONTROL), 0.0f);

    object->setRotation(Quaternion(-rx, vec3(1.0, 0.0, 0.0)) * Quaternion(ry, vec3(0.0, 1.0, 0.0)));
    object->setPosition(object->getPosition() + dt*(vertical + direction * object->getRotation()));
}

#include "CinemaObject.h"
#include <cstring>

using namespace Silexars;
using namespace AEngine::Cinema;
using namespace Math;

CinemaObject::CinemaObject() : position(0.0f), rotation(1.0f, 0.0f, 0.0f, 0.0f), scale(1.0f) { name = new char[1]; name[0] = 0; }
CinemaObject::~CinemaObject() { delete[] name; }

void CinemaObject::setName(const char *name) {
    uint32 l = strlen(name);

    delete[] this->name;
    this->name = new char[l + 1];
    strcpy(this->name, name);
}
const char* CinemaObject::getName() const { return name; }

void CinemaObject::setPosition(const vec3 &position) { this->position = position; }
vec3 CinemaObject::getPosition() const { return position; }

void CinemaObject::setRotation(const vec3& eulerAngles) { this->rotation = Quaternion(eulerAngles); }
void CinemaObject::setRotation(const Quaternion &rotation) { this->rotation = rotation; }
Quaternion CinemaObject::getRotation() const { return rotation; }

void CinemaObject::setScale(const vec3 &scale) { this->scale = scale; }
vec3 CinemaObject::getScale() const { return scale; }

void CinemaObject::lookAt(const vec3 &position, const vec3 &up) { rotation = Quaternion::lookAt(normalize(position - this->position), up); }

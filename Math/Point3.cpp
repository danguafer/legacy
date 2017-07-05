#include "Point3.h"

using namespace Silexars::Math;

Point3::Point3() {}
Point3::Point3(const vec3 &p) {
    this->x = p.x;
    this->y = p.y;
    this->z = p.z;
}

vec3 Point3::operator-(const Point3 &p) const { return vec3(x - p.x, y - p.y, z - p.z); }

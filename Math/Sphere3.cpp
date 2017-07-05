#include "Sphere3.h"

using namespace Silexars::Math;

Sphere3::Sphere3() {}
Sphere3::Sphere3(const Point3 &p0, const float32 radius) {
    c = p0;
    r = radius;
}

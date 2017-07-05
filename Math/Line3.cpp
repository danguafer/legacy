#include "Line3.h"

#include "functions.h"

using namespace Silexars::Math;

Line3::Line3() {}
Line3::Line3(const Point3 &a, const Point3 &b) {
    o = a;
    d = normalize(b - a);
}

Line3::Line3(const Point3 &p0, const vec3 &l) {
    o = p0;
    d = l;
}

bool Line3::intersection(const Sphere3 &g, Point3 *outP) {
    vec3 omc = o - g.c;
    float32 loc = dot(d, omc);
    float32 s = loc * loc - dot(omc, omc) + g.r * g.r;
    if (s < 0.0f) return false;
    if (outP) {
        s = sqrt(s);
        outP[0] = ((vec3) o) + d * (-loc - s);
        outP[1] = ((vec3) o) + d * (-loc + s);
    }
    return true;
}

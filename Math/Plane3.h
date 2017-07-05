#pragma once

#include <Veritas/Definitions/Definitions.h>
#include "Point3.h"
#include "Line3.h"
#include "vec3.h"

namespace Silexars {
    namespace Math {
        class Point3;
        class Line3;
        class Plane3 {
            public:
                Plane3();
                Plane3(const Point3& p, const vec3& d);

                float32 distance(const Point3& p);
                float32 distance(const Line3& l);
                float32 distance(const Plane3& p);

                bool intersection(const Point3& a, Point3 *b);
                bool intersection(const Line3&  l, Point3 *p);
                bool intersection(const Plane3& l, Point3 *p);
        };
    }
}

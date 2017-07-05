#pragma once

#include "Point3.h"

namespace Silexars {
    namespace Math {
        class Line3;
        class Plane3;
        class Sphere3 {
            public:
                Sphere3();
                Sphere3(const Point3 &p0, const float32 radius);

                float32 distance(const Point3  &g);
                float32 distance(const Line3   &g);
                float32 distance(const Plane3  &g);
                float32 distance(const Sphere3 &g);

                bool intersection(const Point3  &g, Point3 *outP = 0);
                bool intersection(const Line3   &g, Point3 *outP = 0);
                bool intersection(const Plane3  &g, Point3 *outP = 0);
                bool intersection(const Sphere3 &g, Point3 *outP = 0);

                Point3 c;
                float32 r;
        };
    }
}

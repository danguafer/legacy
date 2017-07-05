#pragma once

#include <Veritas/Definitions/Definitions.h>

#include "vec3.h"

namespace Silexars {
    namespace Math {
        class Line3;
        class Plane3;
        class Sphere3;
        class Point3 {
            public:
                Point3();
                Point3(float32 x, float32 y, float32 z);
                Point3(const vec3& p);

                float32 distance(const Point3  &g);
                float32 distance(const Line3   &g);
                float32 distance(const Plane3  &g);
                float32 distance(const Sphere3 &g);

                bool intersection(const Point3  &g, Point3 *outP = 0);
                bool intersection(const Line3   &g, Point3 *outP = 0);
                bool intersection(const Plane3  &g, Point3 *outP = 0);
                bool intersection(const Sphere3 &g, Point3 *outP = 0);

                vec3 operator-(const Point3 &p) const;

                float32 x, y, z;
        };
    }
}

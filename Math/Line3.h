#pragma once

#include <Veritas/Definitions/Definitions.h>
#include "Point3.h"
#include "Plane3.h"
#include "vec3.h"
#include "Sphere3.h"

namespace Silexars {
    namespace Math {
        class Plane3;
        class Line3 {
            public:
                Line3();
                Line3(const Point3& a, const Point3& b);
                Line3(const Point3& p0, const vec3& l);

                float32 distance(const Point3  &g);
                float32 distance(const Line3   &g);
                float32 distance(const Plane3  &g);
                float32 distance(const Sphere3 &g);

                bool intersection(const Point3  &g, Point3 *outP = 0);
                bool intersection(const Line3   &g, Point3 *outP = 0);
                bool intersection(const Plane3  &g, Point3 *outP = 0);
                bool intersection(const Sphere3 &g, Point3 *outP = 0);

                Point3 o;
                vec3 d;
        };
    }
}

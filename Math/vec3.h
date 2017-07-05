#pragma once

#include <Veritas/Definitions/Definitions.h>
#include "vec2.h"
#include <ostream>

namespace Silexars {
    namespace Math {
        class Point3;
        class vec3 {
            public:
                vec3();
                vec3(float32 value);
                vec3(float32 x, float32 y, float32 z);
                vec3(const vec2 &xy, float32 z);
                vec3(float32 x, const vec2 &yz);
                vec3(const Point3 &p);

                float32 length() const;
                void normalize();
                void crucify(const vec3& v); // lol
                void reflect(const vec3& n);
                void refract(const vec3& n, float32 eta);

                vec3 operator+(float32 s) const;
                vec3 operator-(float32 s) const;
                vec3 operator*(float32 s) const;
                vec3 operator/(float32 s) const;

                void operator+=(float32 s);
                void operator-=(float32 s);
                void operator*=(float32 s);
                void operator/=(float32 s);

                vec3 operator+(const vec3& v) const;
                vec3 operator-(const vec3& v) const;
                vec3 operator*(const vec3& v) const;
                vec3 operator/(const vec3& v) const;

                void operator+=(const vec3& v);
                void operator-=(const vec3& v);
                void operator*=(const vec3& v);
                void operator/=(const vec3& v);

                vec3 operator-() const;

                bool operator!=(const vec3& v) const;
                bool operator==(const vec3& v) const;

                float32 x, y, z;
        };
    }
}

Silexars::Math::vec3 operator*(const float32 s, const Silexars::Math::vec3& v);

std::ostream& operator<<(std::ostream &os, const Silexars::Math::vec3& v);


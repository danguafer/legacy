#pragma once

#include <Veritas/Definitions/Definitions.h>

#include "Complex.h"
#include "vec3.h"

namespace Silexars {
    namespace Math {
        class Quaternion {
            public:
                Quaternion();
                Quaternion(float32 a, float32 b, float32 c, float32 d);
                Quaternion(const Complex& ab, const Complex& cd);
                Quaternion(float32 angle, const vec3& axis);
                Quaternion(const vec3& eulerAngles);

                float32 a, b, c, d;

                Quaternion operator+(const Quaternion& q) const;
                Quaternion operator-(const Quaternion& q) const;
                Quaternion operator*(const Quaternion& q) const;
                Quaternion operator/(const Quaternion& q) const;

                Quaternion operator+(const float32 s) const;
                Quaternion operator-(const float32 s) const;
                Quaternion operator*(const float32 s) const;
                Quaternion operator/(const float32 s) const;

                vec3 operator*(const vec3& v) const;

                void operator+=(const Quaternion& q);
                void operator-=(const Quaternion& q);
                void operator*=(const Quaternion& q);
                void operator/=(const Quaternion& q);

                void operator+=(const float32 s);
                void operator-=(const float32 s);
                void operator*=(const float32 s);
                void operator/=(const float32 s);

                void normalize();

                Quaternion operator-() const;

                static Quaternion lookAt(const vec3& direction, const vec3& up);

                void conjugate();
        };
    }
}

Silexars::Math::Quaternion operator+(const float32 s, const Silexars::Math::Quaternion& c);
Silexars::Math::Quaternion operator-(const float32 s, const Silexars::Math::Quaternion& c);
Silexars::Math::Quaternion operator*(const float32 s, const Silexars::Math::Quaternion& c);
Silexars::Math::Quaternion operator/(const float32 s, const Silexars::Math::Quaternion& c);
Silexars::Math::vec3 operator*(const Silexars::Math::vec3& v, const Silexars::Math::Quaternion& q);

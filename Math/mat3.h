#pragma once

#include <Veritas/Definitions/Definitions.h>
#include "vec2.h"
#include "vec3.h"
#include "Quaternion.h"

#include "mat4.h"

namespace Silexars {
    namespace Math {
        class mat3 {
            public:
                mat3();
                mat3(float32 m00, float32 m01, float32 m02,
                     float32 m10, float32 m11, float32 m12,
                     float32 m20, float32 m21, float32 m22);
                mat3(const vec3 &l0, const vec3 &l1, const vec3 &l2);
                mat3(const mat4& m);

                mat3 operator+(const mat3 &m) const;
                mat3 operator-(const mat3 &m) const;
                mat3 operator*(const mat3 &m) const;
                mat3 operator*(const float32 s) const;

                void operator+=(const mat3 &m);
                void operator-=(const mat3 &m);
                void operator*=(const mat3 &m);
                void operator*=(const float32 s);

                static mat3 identity();

                static mat3 translation(const vec2 &translation);

                static mat3 scaling(const vec2 &scaling);
                static mat3 scaling(const vec3 &scaling);

                static mat3 xRotation(float32 a);
                static mat3 yRotation(float32 a);
                static mat3 zRotation(float32 a);
                static mat3 rotation(const Quaternion& q);

                static mat3 lookAt(const vec3 &direction, const vec3 &up);

                float32 m[9];
        };
    }
}

Silexars::Math::mat3 operator*(const float32 s, const Silexars::Math::mat3& m);

std::ostream& operator<<(std::ostream &os, const Silexars::Math::mat3& v);

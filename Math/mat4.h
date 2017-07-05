#pragma once

#include <Veritas/Definitions/Definitions.h>
#include "vec4.h"
#include "Quaternion.h"

namespace Silexars {
    namespace Math {
        class mat4 {
            public:
                mat4();
                mat4(float32 m00, float32 m01, float32 m02, float32 m03,
                     float32 m10, float32 m11, float32 m12, float32 m13,
                     float32 m20, float32 m21, float32 m22, float32 m23,
                     float32 m30, float32 m31, float32 m32, float32 m33);
                mat4(const vec4& l0, const vec4& l1, const vec4& l2, const vec4& l3);

                mat4 operator+(const mat4 &m) const;
                mat4 operator-(const mat4 &m) const;
                mat4 operator*(const mat4 &m) const;
                mat4 operator*(const float32 s) const;
                mat4 entrywiseProduct(const mat4 &m) const;

                void operator+=(const mat4 &m);
                void operator-=(const mat4 &m);
                void operator*=(const mat4 &m);
                void operator*=(const float32 s);

                static mat4 identity();
                static mat4 perspective(float32 fov, float32 aspect, float32 near, float32 far);
                static mat4 orthographic(float32 left, float32 right, float32 bottom, float32 top, float32 near, float32 far);
                static mat4 orthographic(float32 width, float32 height, float32 depth);

                static mat4 translation(const vec3 &translation);

                static mat4 scaling(const vec3 &scaling);
                static mat4 scaling(const vec4 &scaling);

                static mat4 xRotation(float32 a);
                static mat4 yRotation(float32 a);
                static mat4 zRotation(float32 a);
                static mat4 rotation(const Quaternion& q);

                static mat4 lookAt(const vec3 &direction, const vec3 &up);

                float32 m[16];
        };
    }
}

Silexars::Math::mat4 operator*(const float32 s, const Silexars::Math::mat4& m);

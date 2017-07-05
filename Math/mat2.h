#pragma once
#include <Veritas/Definitions/Definitions.h>
#include "vec2.h"

#include "mat3.h"

namespace Silexars {
    namespace Math {
        class mat2 {
            public:
                mat2();
                mat2(float32 m00, float32 m01,
                     float32 m10, float32 m11);
                mat2(const vec2& l0, const vec2& l1);
                mat2(const mat3& m);
                mat2(const mat4& m);

                mat2 operator+(const mat2 &m) const;
                mat2 operator-(const mat2 &m) const;
                mat2 operator*(const mat2 &m) const;
                mat2 operator*(const float32 s) const;

                void operator+=(const mat2 &m);
                void operator-=(const mat2 &m);
                void operator*=(const mat2 &m);
                void operator*=(const float32 s);

                static mat2 identity();
                static mat2 rotation(float32 a);

                float32 m[4];
        };
    }
}

Silexars::Math::mat2 operator*(const float32 s, const Silexars::Math::mat2& m);

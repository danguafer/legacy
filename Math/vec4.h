#pragma once

#include <Veritas/Definitions/Definitions.h>
#include "vec2.h"
#include "vec3.h"

namespace Silexars {
    namespace Math {
        class vec4 {
            public:
                vec4();
                vec4(float32 value);
                vec4(float32 x, float32 y, float32 z, float32 w);
                vec4(const vec2 &xy, float32 z, float32 w);
                vec4(const vec2 &xy, const vec2 &zw);
                vec4(const vec3 &xyz, float32 w);
                vec4(float32 x, const vec3 &yzw);

                vec4 operator+(float32 s) const;
                vec4 operator-(float32 s) const;
                vec4 operator*(float32 s) const;
                vec4 operator/(float32 s) const;

                void operator+=(float32 s);
                void operator-=(float32 s);
                void operator*=(float32 s);
                void operator/=(float32 s);

                vec4 operator+(const vec4& v) const;
                vec4 operator-(const vec4& v) const;
                vec4 operator*(const vec4& v) const;
                vec4 operator/(const vec4& v) const;

                void operator+=(const vec4& v);
                void operator-=(const vec4& v);
                void operator*=(const vec4& v);
                void operator/=(const vec4& v);

                vec4 operator-() const;

                bool operator!=(const vec4& v) const;
                bool operator==(const vec4& v) const;

                float32 x, y, z, w;
        };
    }
}

Silexars::Math::vec4 operator*(const float32 s, const Silexars::Math::vec4& v);

std::ostream& operator<<(std::ostream &os, const Silexars::Math::vec4& v);

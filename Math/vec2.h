#pragma once

#include <Veritas/Definitions/Definitions.h>
#include <ostream>

namespace Silexars {
    namespace Math {
        class vec2 {
            public:
                vec2();
                vec2(float32 value);
                vec2(float32 x, float32 y);

                vec2 operator+(float32 s) const;
                vec2 operator-(float32 s) const;
                vec2 operator*(float32 s) const;
                vec2 operator/(float32 s) const;

                void operator+=(float32 s);
                void operator-=(float32 s);
                void operator*=(float32 s);
                void operator/=(float32 s);

                vec2 operator+(const vec2& v) const;
                vec2 operator-(const vec2& v) const;
                vec2 operator*(const vec2& v) const;
                vec2 operator/(const vec2& v) const;

                void operator+=(const vec2& v);
                void operator-=(const vec2& v);
                void operator*=(const vec2& v);
                void operator/=(const vec2& v);

                vec2 operator-() const;

                bool operator==(const vec2& v) const;
                bool operator!=(const vec2& v) const;

                float32 x, y;
        };
    }
}

Silexars::Math::vec2 operator*(const float32 s, const Silexars::Math::vec2& v);

std::ostream& operator<<(std::ostream &os, const Silexars::Math::vec2& v);

#pragma once

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"

#include "mat2.h"
#include "mat3.h"
#include "mat4.h"

#include "Complex.h"
#include "Quaternion.h"

#include <math.h>

namespace Silexars {
    namespace Math {
        float32 random();
        float32 random(float32 x);
        vec2 random(const vec2& x);
        vec3 random(const vec3& x);
        vec4 random(const vec4& x);

        float32 length(const float32 s);
        float32 length(const vec2& v);
        float32 length(const vec3& v);
        float32 length(const vec4& v);
        float32 length(const Complex& c);
        float32 length(const Quaternion& q);

        float32 distance(const float32 a, const float32 b);
        float32 distance(const vec2& a, const vec2& b);
        float32 distance(const vec3& a, const vec3& b);
        float32 distance(const vec4& a, const vec4& b);

        float32 dot(const float32 a, const float32 b);
        float32 dot(const vec2& a, const vec2& b);
        float32 dot(const vec3& a, const vec3& b);
        float32 dot(const vec4& a, const vec4& b);

        vec3 cross(const vec3& a, const vec3& b);

        float32 reflect(const float32 v, const float32 n);
        vec2 reflect(const vec2& v, const vec2& n);
        vec3 reflect(const vec3& v, const vec3& n);
        vec4 reflect(const vec4& v, const vec4& n);

        float32 refract(const float32 v, const float32 n, float32 index);
        vec2 refract(const vec2& v, const vec2& n, float32 index);
        vec3 refract(const vec3& v, const vec3& n, float32 index);
        vec4 refract(const vec4& v, const vec4& n, float32 index);

        float32 normalize(const float32 s);
        vec2 normalize(const vec2& v);
        vec3 normalize(const vec3& v);
        vec4 normalize(const vec4& v);

        float32 abs(const float32 s);
        vec2 abs(const vec2& v);
        vec3 abs(const vec3& v);
        vec4 abs(const vec4& v);

        float32 sign(const float32 s);
        vec2 sign(const vec2& v);
        vec3 sign(const vec3& v);
        vec4 sign(const vec4& v);

        float32 floor(const float32 s);
        vec2 floor(const vec2& v);
        vec3 floor(const vec3& v);
        vec4 floor(const vec4& v);

        float32 ceil(const float32 s);
        vec2 ceil(const vec2& v);
        vec3 ceil(const vec3& v);
        vec4 ceil(const vec4& v);

        float32 fract(const float32 s);
        vec2 fract(const vec2& v);
        vec3 fract(const vec3& v);
        vec4 fract(const vec4& v);

        float32 mod(const float32 a, const float32 b);
        vec2 mod(const vec2& v, const vec2& u);
        vec2 mod(const vec2& v, const float32 s);
        vec3 mod(const vec3& v, const vec3& u);
        vec3 mod(const vec3& v, const float32 s);
        vec4 mod(const vec4& v, const vec4& u);
        vec4 mod(const vec4& v, const float32 s);

        float32 min(const float32 a, const float32 b);
        vec2 min(const vec2& v, const vec2& u);
        vec2 min(const vec2& v, const float32 s);
        vec3 min(const vec3& v, const vec3& u);
        vec3 min(const vec3& v, const float32 s);
        vec4 min(const vec4& v, const vec4& u);
        vec4 min(const vec4& v, const float32 s);

        float32 max(const float32 a, const float32 b);
        vec2 max(const vec2& v, const vec2& u);
        vec2 max(const vec2& v, const float32 s);
        vec3 max(const vec3& v, const vec3& u);
        vec3 max(const vec3& v, const float32 s);
        vec4 max(const vec4& v, const vec4& u);
        vec4 max(const vec4& v, const float32 s);

        float32 clamp(const float32 a, const float32 min, const float32 max);
        vec2 clamp(const vec2& v, const vec2& min, const vec2& max);
        vec2 clamp(const vec2& v, const float32 min, const float32 max);
        vec3 clamp(const vec3& v, const vec3& min, const vec3& max);
        vec3 clamp(const vec3& v, const float32 min, const float32 max);
        vec4 clamp(const vec4& v, const vec4& min, const vec4& max);
        vec4 clamp(const vec4& v, const float32 min, const float32 max);

        float32 mix(const float32 a, const float32 b, const float32 x);
        vec2 mix(const vec2& a, const vec2& b, const vec2& x);
        vec2 mix(const vec2& a, const vec2& b, const float32 x);
        vec3 mix(const vec3& a, const vec3& b, const vec3& x);
        vec3 mix(const vec3& a, const vec3& b, const float32 x);
        vec4 mix(const vec4& a, const vec4& b, const vec4& x);
        vec4 mix(const vec4& a, const vec4& b, const float32 x);

        float32 step(const float32 edge, const float32 x);
        vec2 step(const vec2& edge, const vec2& x);
        vec2 step(const float32 edge, const vec2& x);
        vec3 step(const vec3& edge, const vec3& x);
        vec3 step(const float32 edge, const vec3& x);
        vec4 step(const vec4& edge, const vec4& x);
        vec4 step(const float32 edge, const vec4& x);

        float32 smoothstep(const float32 a, const float32 b, const float32 x);
        vec2 smoothstep(const vec2& a, const vec2& b, const vec2& x);
        vec2 smoothstep(const float32 a, const float32 b, const vec2& x);
        vec3 smoothstep(const vec3& a, const vec3& b, const vec3& x);
        vec3 smoothstep(const float32 a, const float32 b, const vec3& x);
        vec4 smoothstep(const vec4& a, const vec4& b, const vec4& x);
        vec4 smoothstep(const float32 a, const float32 b, const vec4& x);

        Complex conjugate(const Complex& c);
        Quaternion conjugate(const Quaternion& q);

        mat2 transpose(const mat2& m);
        mat3 transpose(const mat3& m);
        mat4 transpose(const mat4& m);

        mat2 inverse(const mat2& m);
        mat3 inverse(const mat3& m);
        mat4 inverse(const mat4& m);

        float32 determinant(const mat2& m);
        float32 determinant(const mat3& m);
        float32 determinant(const mat4& m);

        float32 sin(float32 x);
        vec2 sin(const vec2& x);
        vec3 sin(const vec3& x);
        vec4 sin(const vec4& x);

        float32 cos(float32 x);
        vec2 cos(const vec2& x);
        vec3 cos(const vec3& x);
        vec4 cos(const vec4& x);

        vec3 slerp(const vec3& start, const vec3& end, float32 x);
    }
}

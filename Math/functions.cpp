#include "functions.h"

#include <cmath>
#include <cstdlib>

using namespace Silexars;
using namespace Math;

Complex Math::conjugate(const Complex &c) { return Complex(c.a, -c.b); }
Quaternion Math::conjugate(const Quaternion &q) { return Quaternion(q.a, -q.b, -q.c, -q.d); }

float32 Math::random() { return (rand()/(float32) RAND_MAX - 0.5f)*2.0f; }
float32 Math::random(float32 x) { return (fract(sin(x) * 456.678f) - 0.5f)*2.0f; }
vec2 Math::random(const vec2 &v) { return vec2(random(v.x), random(v.y)); }
vec3 Math::random(const vec3 &v) { return vec3(random(v.x), random(v.y), random(v.z)); }
vec4 Math::random(const vec4 &v) { return vec4(random(v.x), random(v.y), random(v.z), random(v.w)); }

float32 Math::length(const float32 s) { return sqrt(s*s); }
float32 Math::length(const vec2 &v) { return sqrt(v.x*v.x + v.y*v.y); }
float32 Math::length(const vec3 &v) { return sqrt(v.x*v.x + v.y*v.y + v.z*v.z); }
float32 Math::length(const vec4 &v) { return sqrt(v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w); }

float32 Math::length(const Quaternion &q) { return sqrt(q.a*q.a + q.b*q.b + q.c*q.c + q.d*q.d); }
float32 Math::length(const Complex &c) { return sqrt(c.a*c.a + c.b*c.b); }

float32 Math::normalize(const float32 s) {
    if (s == 0.0f) return s;
    return s/length(s);
}
vec2 Math::normalize(const vec2 &v) {
    float32 l = length(v);
    if (l == 0.0f) return v;
    return v/l;
}
vec3 Math::normalize(const vec3 &v) {
    float32 l = length(v);
    if (l == 0.0f) return v;
    return v/l;
}
vec4 Math::normalize(const vec4 &v) {
    float32 l = length(v);
    if (l == 0.0f) return v;
    return v/l;
}

float32 Math::dot(const float32 a, const float32 b) { return a*b; }
float32 Math::dot(const vec2 &a, const vec2 &b) { return a.x*b.x + a.y*b.y; }
float32 Math::dot(const vec3 &a, const vec3 &b) { return a.x*b.x + a.y*b.y + a.z*b.z; }
float32 Math::dot(const vec4 &a, const vec4 &b) { return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w; }

float32 Math::distance(const float32 a, const float32 b) { return length(b - a); }
float32 Math::distance(const vec2 &a, const vec2 &b) { return length(b - a); }
float32 Math::distance(const vec3 &a, const vec3 &b) { return length(b - a); }
float32 Math::distance(const vec4 &a, const vec4 &b) { return length(b - a); }

vec3 Math::cross(const vec3 &a, const vec3 &b) { return vec3(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x); }

float32 Math::mix(const float32 a, const float32 b, const float32 x) { return a + (b - a)*x; }
vec2 Math::mix(const vec2& a, const vec2& b, const float32 x) { return a + (b - a)*x; }
vec2 Math::mix(const vec2& a, const vec2& b, const vec2& x)   { return a + (b - a)*x; }
vec3 Math::mix(const vec3& a, const vec3& b, const float32 x) { return a + (b - a)*x; }
vec3 Math::mix(const vec3& a, const vec3& b, const vec3& x)   { return a + (b - a)*x; }
vec4 Math::mix(const vec4& a, const vec4& b, const float32 x) { return a + (b - a)*x; }
vec4 Math::mix(const vec4& a, const vec4& b, const vec4& x)   { return a + (b - a)*x; }

float32 Math::min(const float32 a, const float32 b) { return a < b ? a : b; }
vec2 Math::min(const vec2 &v, const float32 s) { return vec2(min(v.x, s), min(v.y, s)); }
vec2 Math::min(const vec2 &v, const vec2 &u)   { return vec2(min(v.x, u.x), min(v.y, u.y)); }
vec3 Math::min(const vec3 &v, const float32 s) { return vec3(min(v.x, s), min(v.y, s), min(v.z, s)); }
vec3 Math::min(const vec3 &v, const vec3 &u)   { return vec3(min(v.x, u.x), min(v.y, u.y), min(v.z, u.z)); }
vec4 Math::min(const vec4 &v, const float32 s) { return vec4(min(v.x, s), min(v.y, s), min(v.z, s), min(v.w, s)); }
vec4 Math::min(const vec4 &v, const vec4 &u)   { return vec4(min(v.x, u.x), min(v.y, u.y), min(v.z, u.z), min(v.w, u.w)); }

float32 Math::max(const float32 a, const float32 b) { return fmaxf(a, b); }
vec2 Math::max(const vec2 &v, const float32 s) { return vec2(max(v.x, s), max(v.y, s)); }
vec2 Math::max(const vec2 &v, const vec2 &u)   { return vec2(max(v.x, u.x), max(v.y, u.y)); }
vec3 Math::max(const vec3 &v, const float32 s) { return vec3(max(v.x, s), max(v.y, s), max(v.z, s)); }
vec3 Math::max(const vec3 &v, const vec3 &u)   { return vec3(max(v.x, u.x), max(v.y, u.y), max(v.z, u.z)); }
vec4 Math::max(const vec4 &v, const float32 s) { return vec4(max(v.x, s), max(v.y, s), max(v.z, s), max(v.w, s)); }
vec4 Math::max(const vec4 &v, const vec4 &u)   { return vec4(max(v.x, u.x), max(v.y, u.y), max(v.z, u.z), max(v.w, u.w)); }

float32 Math::clamp(const float32 a, const float32 lower, const float32 upper) { return min(max(a, lower), upper); }
vec2 Math::clamp(const vec2 &v, const float32 l, const float32 u) { return vec2(clamp(v.x, l, u), clamp(v.y, l, u)); }
vec2 Math::clamp(const vec2 &v, const vec2 &l, const vec2 &u)     { return vec2(clamp(v.x, l.x, u.x), clamp(v.y, l.y, u.y)); }
vec3 Math::clamp(const vec3 &v, const float32 l, const float32 u) { return vec3(clamp(v.x, l, u), clamp(v.y, l, u), clamp(v.z, l, u)); }
vec3 Math::clamp(const vec3 &v, const vec3 &l, const vec3 &u)     { return vec3(clamp(v.x, l.x, u.x), clamp(v.y, l.y, u.y), clamp(v.z, l.z, u.z)); }
vec4 Math::clamp(const vec4 &v, const float32 l, const float32 u) { return vec4(clamp(v.x, l, u), clamp(v.y, l, u), clamp(v.z, l, u), clamp(v.w, l, u)); }
vec4 Math::clamp(const vec4 &v, const vec4 &l, const vec4 &u)     { return vec4(clamp(v.x, l.x, u.x), clamp(v.y, l.y, u.y), clamp(v.z, l.z, u.z), clamp(v.w, l.w, u.w)); }

float32 Math::floor(const float32 s) { return ::floorf(s); }
vec2 Math::floor(const vec2 &v) { return vec2(floor(v.x), floor(v.y)); }
vec3 Math::floor(const vec3 &v) { return vec3(floor(v.x), floor(v.y), floor(v.z)); }
vec4 Math::floor(const vec4 &v) { return vec4(floor(v.x), floor(v.y), floor(v.z), floor(v.w)); }

float32 Math::ceil(const float32 s) { return ::ceilf(s); }
vec2 Math::ceil(const vec2 &v) { return vec2(ceil(v.x), ceil(v.y)); }
vec3 Math::ceil(const vec3 &v) { return vec3(ceil(v.x), ceil(v.y), ceil(v.z)); }
vec4 Math::ceil(const vec4 &v) { return vec4(ceil(v.x), ceil(v.y), ceil(v.z), ceil(v.w)); }

float32 Math::fract(const float32 s) { return s - floor(s); }
vec2 Math::fract(const vec2 &v) { return vec2(fract(v.x), fract(v.y)); }
vec3 Math::fract(const vec3 &v) { return vec3(fract(v.x), fract(v.y), fract(v.z)); }
vec4 Math::fract(const vec4 &v) { return vec4(fract(v.x), fract(v.y), fract(v.z), fract(v.w)); }

float32 Math::abs(const float32 s) { return fabsf(s); }
vec2 Math::abs(const vec2 &v) { return vec2(abs(v.x), abs(v.y)); }
vec3 Math::abs(const vec3 &v) { return vec3(abs(v.x), abs(v.y), abs(v.z)); }
vec4 Math::abs(const vec4 &v) { return vec4(abs(v.x), abs(v.y), abs(v.z), abs(v.w)); }

float32 Math::sign(const float32 s) { return s < 0.0f ? -1.0f : 1.0f; }
vec2 Math::sign(const vec2 &v) { return vec2(sign(v.x), sign(v.y)); }
vec3 Math::sign(const vec3 &v) { return vec3(sign(v.x), sign(v.y), sign(v.z)); }
vec4 Math::sign(const vec4 &v) { return vec4(sign(v.x), sign(v.y), sign(v.z), sign(v.w)); }

float32 Math::mod(const float32 a, const float32 b) { return fmodf(a, b); }
vec2 Math::mod(const vec2 &v, const float32 s) { return vec2(mod(v.x, s), mod(v.y, s)); }
vec2 Math::mod(const vec2 &v, const vec2 &u)   { return vec2(mod(v.x, u.x), mod(v.y, u.y)); }
vec3 Math::mod(const vec3 &v, const float32 s) { return vec3(mod(v.x, s), mod(v.y, s), mod(v.z, s)); }
vec3 Math::mod(const vec3 &v, const vec3 &u)   { return vec3(mod(v.x, u.x), mod(v.y, u.y), mod(v.z, u.z)); }
vec4 Math::mod(const vec4 &v, const float32 s) { return vec4(mod(v.x, s), mod(v.y, s), mod(v.z, s), mod(v.w, s)); }
vec4 Math::mod(const vec4 &v, const vec4 &u)   { return vec4(mod(v.x, u.x), mod(v.y, u.y), mod(v.z, u.z), mod(v.w, u.w)); }

float32 Math::step(const float32 edge, const float32 x) { return x >= edge ? 1.0f : 0.0f; }
vec2 Math::step(const float32 edge, const vec2 &v) { return vec2(step(edge, v.x), step(edge, v.y)); }
vec2 Math::step(const vec2 &edge, const vec2 &v)   { return vec2(step(edge.x, v.x), step(edge.y, v.y)); }
vec3 Math::step(const float32 edge, const vec3 &v) { return vec3(step(edge, v.x), step(edge, v.y), step(edge, v.z)); }
vec3 Math::step(const vec3 &edge, const vec3 &v)   { return vec3(step(edge.x, v.x), step(edge.y, v.y), step(edge.z, v.z)); }
vec4 Math::step(const float32 edge, const vec4 &v) { return vec4(step(edge, v.x), step(edge, v.y), step(edge, v.z), step(edge, v.w)); }
vec4 Math::step(const vec4 &edge, const vec4 &v)   { return vec4(step(edge.x, v.x), step(edge.y, v.y), step(edge.z, v.z), step(edge.w, v.w)); }

float32 Math::smoothstep(const float32 a, const float32 b, const float32 x) {
    if (b < a) return smoothstep(b, a, b + a - x);
    if (x < a) return 0.0f;
    if (x > b) return 1.0f;
    float32 y = (x - a)/(b - a);
    return y*y*(3.0f - 2.0f*y);
}
vec2 Math::smoothstep(const float32 a, const float32 b, const vec2 &v) { return vec2(smoothstep(a, b, v.x), smoothstep(a, b, v.y)); }
vec2 Math::smoothstep(const vec2 &a, const vec2 &b, const vec2 &v)     { return vec2(smoothstep(a.x, b.x, v.x), smoothstep(a.y, b.y, v.y)); }
vec3 Math::smoothstep(const float32 a, const float32 b, const vec3 &v) { return vec3(smoothstep(a, b, v.x), smoothstep(a, b, v.y), smoothstep(a, b, v.z)); }
vec3 Math::smoothstep(const vec3 &a, const vec3 &b, const vec3 &v)     { return vec3(smoothstep(a.x, b.x, v.x), smoothstep(a.y, b.y, v.y), smoothstep(a.z, b.z, v.z)); }
vec4 Math::smoothstep(const float32 a, const float32 b, const vec4 &v) { return vec4(smoothstep(a, b, v.x), smoothstep(a, b, v.y), smoothstep(a, b, v.z), smoothstep(a, b, v.w)); }
vec4 Math::smoothstep(const vec4 &a, const vec4 &b, const vec4 &v)     { return vec4(smoothstep(a.x, b.x, v.x), smoothstep(a.y, b.y, v.y), smoothstep(a.z, b.z, v.z), smoothstep(a.w, b.w, v.w)); }

float32 Math::reflect(const float32 v, const float32 n) { return v - 2.0f*dot(v, n)*n; }
vec2 Math::reflect(const vec2 &v, const vec2 &n)        { return v - 2.0f*dot(v, n)*n; }
vec3 Math::reflect(const vec3 &v, const vec3 &n)        { return v - 2.0f*dot(v, n)*n; }
vec4 Math::reflect(const vec4 &v, const vec4 &n)        { return v - 2.0f*dot(v, n)*n; }

float32 Math::refract(const float32 v, const float32 n, float32 eta) {
    float32 d = dot(n, v);
    float32 k = 1.0f - eta*eta * (1.0f - d*d);
    return k < 0.0f ? 0.0f : eta * v - (eta*d + sqrt(k))*n;
}
vec2 Math::refract(const vec2 &v, const vec2 &n, float32 eta) {
    float32 d = dot(n, v);
    float32 k = 1.0f - eta*eta * (1.0f - d*d);
    return k < 0.0f ? 0.0f : eta * v - (eta*d + sqrt(k))*n;
}
vec3 Math::refract(const vec3 &v, const vec3 &n, float32 eta) {
    float32 d = dot(n, v);
    float32 k = 1.0f - eta*eta * (1.0f - d*d);
    return k < 0.0f ? 0.0f : eta * v - (eta*d + sqrt(k))*n;
}
vec4 Math::refract(const vec4 &v, const vec4 &n, float32 eta) {
    float32 d = dot(n, v);
    float32 k = 1.0f - eta*eta * (1.0f - d*d);
    return k < 0.0f ? 0.0f : eta * v - (eta*d + sqrt(k))*n;
}

float32 Math::determinant(const mat2 &m) { return m.m[0]*m.m[3] - m.m[1]*m.m[2]; }
float32 Math::determinant(const mat3 &m) { return m.m[0]*m.m[4]*m.m[8] + m.m[1]*m.m[5]*m.m[6] + m.m[2]*m.m[3]*m.m[7] - m.m[2]*m.m[4]*m.m[6] - m.m[1]*m.m[3]*m.m[8] - m.m[0]*m.m[5]*m.m[7]; }
float32 Math::determinant(const mat4 &m) { return m.m[0]*m.m[5]*m.m[10]*m.m[15] + m.m[1]*m.m[6]*m.m[11]*m.m[12] + m.m[2]*m.m[7]*m.m[8]*m.m[13] + m.m[3]*m.m[4]*m.m[9]*m.m[14] - m.m[3]*m.m[6]*m.m[9]*m.m[12] - m.m[2]*m.m[5]*m.m[8]*m.m[15] - m.m[1]*m.m[4]*m.m[11]*m.m[14] - m.m[0]*m.m[7]*m.m[10]*m.m[13]; }

mat2 Math::transpose(const mat2 &m) {
    return mat2(m.m[0], m.m[2],
                m.m[1], m.m[3]);
}

mat3 Math::transpose(const mat3 &m) {
    return mat3(m.m[0], m.m[3], m.m[6],
                m.m[1], m.m[4], m.m[7],
                m.m[2], m.m[5], m.m[8]);
}

mat4 Math::transpose(const mat4 &m) {
    return mat4(m.m[ 0], m.m[ 1], m.m[ 2], m.m[ 3],
                m.m[ 4], m.m[ 5], m.m[ 6], m.m[ 7],
                m.m[ 8], m.m[ 9], m.m[10], m.m[11],
                m.m[12], m.m[13], m.m[14], m.m[15]);
}

mat2 Math::inverse(const mat2 &m) {
    return (1.0f/determinant(m))*mat2( m.m[3], -m.m[1],
                                      -m.m[2],  m.m[0]);
}

mat3 Math::inverse(const mat3 &m) {
    float32 A = m.m[4]*m.m[8]-m.m[5]*m.m[7];
    float32 B = m.m[5]*m.m[6]-m.m[3]*m.m[8];
    float32 C = m.m[3]*m.m[7]-m.m[4]*m.m[6];
    float32 det = m.m[0]*A + m.m[1]*B + m.m[2]*C; // faster way to get det
    return (1.0f/det)*mat3(A, m.m[2]*m.m[7]-m.m[1]*m.m[8], m.m[1]*m.m[5]-m.m[2]*m.m[4],
                           B, m.m[0]*m.m[8]-m.m[2]*m.m[6], m.m[2]*m.m[3]-m.m[0]*m.m[5],
                           C, m.m[1]*m.m[6]-m.m[0]*m.m[7], m.m[0]*m.m[4]-m.m[1]*m.m[3]);
}

mat4 Math::inverse(const mat4 &m) {
    //http://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix
    float32 inv[16];

    #define m m.m
    inv[0] = m[5]  * m[10] * m[15] -
             m[5]  * m[11] * m[14] -
             m[9]  * m[6]  * m[15] +
             m[9]  * m[7]  * m[14] +
             m[13] * m[6]  * m[11] -
             m[13] * m[7]  * m[10];

    inv[4] = -m[4]  * m[10] * m[15] +
              m[4]  * m[11] * m[14] +
              m[8]  * m[6]  * m[15] -
              m[8]  * m[7]  * m[14] -
              m[12] * m[6]  * m[11] +
              m[12] * m[7]  * m[10];

    inv[8] = m[4]  * m[9] * m[15] -
             m[4]  * m[11] * m[13] -
             m[8]  * m[5] * m[15] +
             m[8]  * m[7] * m[13] +
             m[12] * m[5] * m[11] -
             m[12] * m[7] * m[9];

    inv[12] = -m[4]  * m[9] * m[14] +
               m[4]  * m[10] * m[13] +
               m[8]  * m[5] * m[14] -
               m[8]  * m[6] * m[13] -
               m[12] * m[5] * m[10] +
               m[12] * m[6] * m[9];

    inv[1] = -m[1]  * m[10] * m[15] +
              m[1]  * m[11] * m[14] +
              m[9]  * m[2] * m[15] -
              m[9]  * m[3] * m[14] -
              m[13] * m[2] * m[11] +
              m[13] * m[3] * m[10];

    inv[5] = m[0]  * m[10] * m[15] -
             m[0]  * m[11] * m[14] -
             m[8]  * m[2] * m[15] +
             m[8]  * m[3] * m[14] +
             m[12] * m[2] * m[11] -
             m[12] * m[3] * m[10];

    inv[9] = -m[0]  * m[9] * m[15] +
              m[0]  * m[11] * m[13] +
              m[8]  * m[1] * m[15] -
              m[8]  * m[3] * m[13] -
              m[12] * m[1] * m[11] +
              m[12] * m[3] * m[9];

    inv[13] = m[0]  * m[9] * m[14] -
              m[0]  * m[10] * m[13] -
              m[8]  * m[1] * m[14] +
              m[8]  * m[2] * m[13] +
              m[12] * m[1] * m[10] -
              m[12] * m[2] * m[9];

    inv[2] = m[1]  * m[6] * m[15] -
             m[1]  * m[7] * m[14] -
             m[5]  * m[2] * m[15] +
             m[5]  * m[3] * m[14] +
             m[13] * m[2] * m[7] -
             m[13] * m[3] * m[6];

    inv[6] = -m[0]  * m[6] * m[15] +
              m[0]  * m[7] * m[14] +
              m[4]  * m[2] * m[15] -
              m[4]  * m[3] * m[14] -
              m[12] * m[2] * m[7] +
              m[12] * m[3] * m[6];

    inv[10] = m[0]  * m[5] * m[15] -
              m[0]  * m[7] * m[13] -
              m[4]  * m[1] * m[15] +
              m[4]  * m[3] * m[13] +
              m[12] * m[1] * m[7] -
              m[12] * m[3] * m[5];

    inv[14] = -m[0]  * m[5] * m[14] +
               m[0]  * m[6] * m[13] +
               m[4]  * m[1] * m[14] -
               m[4]  * m[2] * m[13] -
               m[12] * m[1] * m[6] +
               m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] +
              m[1] * m[7] * m[10] +
              m[5] * m[2] * m[11] -
              m[5] * m[3] * m[10] -
              m[9] * m[2] * m[7] +
              m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] -
             m[0] * m[7] * m[10] -
             m[4] * m[2] * m[11] +
             m[4] * m[3] * m[10] +
             m[8] * m[2] * m[7] -
             m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] +
               m[0] * m[7] * m[9] +
               m[4] * m[1] * m[11] -
               m[4] * m[3] * m[9] -
               m[8] * m[1] * m[7] +
               m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] -
              m[0] * m[6] * m[9] -
              m[4] * m[1] * m[10] +
              m[4] * m[2] * m[9] +
              m[8] * m[1] * m[6] -
              m[8] * m[2] * m[5];

    float32 det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];
    #undef m

    if (det == 0) return mat4(0.0, 0.0, 0.0, 0.0,
                              0.0, 0.0, 0.0, 0.0,
                              0.0, 0.0, 0.0, 0.0,
                              0.0, 0.0, 0.0, 0.0);
    det = 1.0 / det;
    return mat4(inv[ 0], inv[ 1], inv[ 2], inv[ 3],
                inv[ 4], inv[ 5], inv[ 6], inv[ 7],
                inv[ 8], inv[ 9], inv[10], inv[11],
                inv[12], inv[13], inv[14], inv[15]) * det;
}

float32 Math::sin(float32 x) { return ::sin(x); }
vec2 Math::sin(const vec2 &v) { return vec2(sin(v.x), sin(v.y)); }
vec3 Math::sin(const vec3 &v) { return vec3(sin(v.x), sin(v.y), sin(v.z)); }
vec4 Math::sin(const vec4 &v) { return vec4(sin(v.x), sin(v.y), sin(v.z), sin(v.w)); }

float32 Math::cos(float32 x) { return ::cos(x); }
vec2 Math::cos(const vec2 &v) { return vec2(cos(v.x), cos(v.y)); }
vec3 Math::cos(const vec3 &v) { return vec3(cos(v.x), cos(v.y), cos(v.z)); }
vec4 Math::cos(const vec4 &v) { return vec4(cos(v.x), cos(v.y), cos(v.z), cos(v.w)); }

vec3 Math::slerp(const vec3 &start, const vec3 &end, float32 x) {
    float32 d = clamp(dot(start, end), -1.0, 1.0);
    float32 a = acos(d) * x;
    vec3 relativePath = normalize(end - start * d);
    return start * cos(a) + relativePath * sin(a);
}

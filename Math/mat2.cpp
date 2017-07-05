#include "mat2.h"
#include <cmath>

using namespace Silexars::Math;

mat2::mat2() {}
mat2::mat2(float32 m00, float32 m01, float32 m10, float32 m11) {
    m[0] = m00;
    m[1] = m01;
    m[2] = m10;
    m[3] = m11;
}
mat2::mat2(const vec2 &l0, const vec2 &l1) {
    *(vec2*) &m[0] = l0;
    *(vec2*) &m[2] = l1;
}
mat2::mat2(const mat4 &m4) {
    m[0] = m4.m[0];
    m[1] = m4.m[1];
    m[2] = m4.m[4];
    m[3] = m4.m[5];
}
mat2::mat2(const mat3 &m3) {
    m[0] = m3.m[0];
    m[1] = m3.m[1];
    m[2] = m3.m[3];
    m[3] = m3.m[4];
}

void mat2::operator*=(const mat2 &b) { *this = operator*(b); }
void mat2::operator+=(const mat2 &b) {
    m[0] += b.m[0];
    m[1] += b.m[1];
    m[2] += b.m[2];
    m[3] += b.m[3];
}
void mat2::operator-=(const mat2 &b) {
    m[0] -= b.m[0];
    m[1] -= b.m[1];
    m[2] -= b.m[2];
    m[3] -= b.m[3];
}
void mat2::operator*=(const float32 s) {
    m[0] *= s;
    m[1] *= s;
    m[2] *= s;
    m[3] *= s;
}

mat2 mat2::operator*(const mat2 &b) const {
    // not tested
    #define E(M, I, J) M[I*2 + J]
    #define EM(I, J, N) (E(m, I, N)*E(b.m, N, J))
    #define M(I, J) (EM(I, J, 0) + EM(I, J, 1))
    return mat2(M(0,0), M(0,1),
                M(1,0), M(1,1));
    #undef M
    #undef EM
    #undef E
}
mat2 mat2::operator+(const mat2 &b) const {
    return mat2(m[0] + b.m[0], m[1] + b.m[1],
                m[2] + b.m[2], m[3] + b.m[3]);
}
mat2 mat2::operator-(const mat2 &b) const {
    return mat2(m[0] - b.m[0], m[1] - b.m[1],
                m[2] - b.m[2], m[3] - b.m[3]);
}
mat2 mat2::operator*(const float32 s) const {
    return mat2(m[0]*s, m[1]*s,
                m[2]*s, m[3]*s);
}

mat2 mat2::identity() {
    return mat2(1.0, 0.0,
                0.0, 1.0);
}

mat2 mat2::rotation(float32 a) {
    float32 s = sin(a);
    float32 c = cos(a);
    return mat2(c, -s,
                s,  c);
}

mat2 operator*(const float32 s, const mat2& m) { return m*s; }

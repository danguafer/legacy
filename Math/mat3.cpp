#include "mat3.h"
#include <cmath>

#include "functions.h"

using namespace Silexars::Math;

mat3::mat3() {}
mat3::mat3(float32 m00, float32 m01, float32 m02, float32 m10, float32 m11, float32 m12, float32 m20, float32 m21, float32 m22) {
    m[0] = m00;
    m[1] = m01;
    m[2] = m02;
    m[3] = m10;
    m[4] = m11;
    m[5] = m12;
    m[6] = m20;
    m[7] = m21;
    m[8] = m22;
}
mat3::mat3(const vec3 &l0, const vec3 &l1, const vec3 &l2) {
    *(vec3*) &m[0] = l0;
    *(vec3*) &m[3] = l1;
    *(vec3*) &m[6] = l2;
}

mat3::mat3(const mat4 &m4) {
    m[0] = m4.m[0];
    m[1] = m4.m[1];
    m[2] = m4.m[2];
    m[3] = m4.m[4];
    m[4] = m4.m[5];
    m[5] = m4.m[6];
    m[6] = m4.m[8];
    m[7] = m4.m[9];
    m[8] = m4.m[10];
}

void mat3::operator*=(const mat3 &b) { *this = operator*(b); }
mat3 mat3::operator*(const mat3 &b) const {
    #define E(M, I, J) M[I*3 + J]
    #define EM(I, J, N) (E(m, I, N)*E(b.m, N, J))
    #define M(I, J) (EM(I, J, 0) + EM(I, J, 1) + EM(I, J, 2))
    return mat3(M(0,0), M(0,1), M(0,2),
                M(1,0), M(1,1), M(1,2),
                M(2,0), M(2,1), M(2,2));
    #undef M
    #undef EM
    #undef E
}

mat3 mat3::operator*(const float32 s) const {
    return mat3(m[0]*s, m[1]*s, m[2]*s,
                m[3]*s, m[4]*s, m[5]*s,
                m[6]*s, m[7]*s, m[8]*s);
}

mat3 mat3::identity() {
    return mat3(1.0, 0.0, 0.0,
                0.0, 1.0, 0.0,
                0.0, 0.0, 1.0);
}

mat3 mat3::translation(const vec2 &t) {
    return mat3(1.0, 0.0, 0.0,
                0.0, 1.0, 0.0,
                t.x, t.y, 1.0);
}

mat3 mat3::scaling(const vec2 &s) { return scaling(vec3(s, 1.0)); }
mat3 mat3::scaling(const vec3 &s) {
    return mat3(s.x, 0.0, 0.0,
                0.0, s.y, 0.0,
                0.0, 0.0, s.z);
}

mat3 mat3::xRotation(float32 a) {
    float32 s = sin(a);
    float32 c = cos(a);
    return mat3(1.0, 0.0, 0.0,
                0.0,   c,  -s,
                0.0,   s,   c);
}

mat3 mat3::yRotation(float32 a) {
    float32 s = sin(a);
    float32 c = cos(a);
    return mat3(  c, 0.0,   s,
                0.0, 1.0, 0.0,
                 -s, 0.0,   c);
}

mat3 mat3::zRotation(float32 a) {
    float32 s = sin(a);
    float32 c = cos(a);
    return mat3(  c,  -s, 0.0,
                  s,   c, 0.0,
                0.0, 0.0, 1.0);
}

mat3 mat3::rotation(const Quaternion &q) {
    float32 as = q.a*q.a;
    float32 bs = q.b*q.b;
    float32 cs = q.c*q.c;
    float32 ds = q.d*q.d;
    float32 bc2 = q.b*q.c*2.0f;
    float32 ad2 = q.a*q.d*2.0f;
    float32 bd2 = q.b*q.d*2.0f;
    float32 ac2 = q.a*q.c*2.0f;
    float32 cd2 = q.c*q.d*2.0f;
    float32 ab2 = q.a*q.b*2.0f;
    return mat3(as + bs - cs - ds,         bc2 - ad2,         bd2 + ac2,
                        bc2 + ad2, as - bs + cs - ds,         cd2 - ab2,
                        bd2 - ac2,         cd2 + ab2, as - bs - cs + ds);
}

mat3 mat3::lookAt(const vec3 &direction, const vec3 &up) {
    vec3 f = normalize(direction);
    vec3 s = normalize(cross(f, up));
    vec3 u = normalize(cross(s, f));
    return mat3( s.x, u.x, -f.x,
                 s.y, u.y, -f.y,
                 s.z, u.z, -f.z);
}

mat3 operator*(const float32 s, const mat3& m) { return m*s; }

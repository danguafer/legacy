#include "mat4.h"
#include "Math.h"

using namespace Silexars::Math;

mat4::mat4() {}
mat4::mat4(float32 m00, float32 m01, float32 m02, float32 m03, float32 m10, float32 m11, float32 m12, float32 m13, float32 m20, float32 m21, float32 m22, float32 m23, float32 m30, float32 m31, float32 m32, float32 m33) {
    m[ 0] = m00;
    m[ 1] = m01;
    m[ 2] = m02;
    m[ 3] = m03;
    m[ 4] = m10;
    m[ 5] = m11;
    m[ 6] = m12;
    m[ 7] = m13;
    m[ 8] = m20;
    m[ 9] = m21;
    m[10] = m22;
    m[11] = m23;
    m[12] = m30;
    m[13] = m31;
    m[14] = m32;
    m[15] = m33;
}
mat4::mat4(const vec4 &l0, const vec4 &l1, const vec4 &l2, const vec4 &l3) {
    *(vec4*) &m[ 0] = l0;
    *(vec4*) &m[ 4] = l1;
    *(vec4*) &m[ 8] = l2;
    *(vec4*) &m[12] = l3;
}

mat4 mat4::identity() {
    return mat4(1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1);
}

void mat4::operator*=(const mat4 &b) { *this = operator*(b); }
mat4 mat4::operator*(const mat4 &b) const {
    #define E(M, I, J) M[I*4 + J]
    #define EM(I, J, N) (E(m, I, N)*E(b.m, N, J))
    #define M(I, J) (EM(I, J, 0) + EM(I, J, 1) + EM(I, J, 2) + EM(I, J, 3))
    return mat4(M(0,0), M(0,1), M(0,2), M(0,3),
                M(1,0), M(1,1), M(1,2), M(1,3),
                M(2,0), M(2,1), M(2,2), M(2,3),
                M(3,0), M(3,1), M(3,2), M(3,3));
    #undef M
    #undef EM
    #undef E
}

mat4 mat4::operator*(const float32 s) const {
    return mat4(m[ 0]*s, m[ 1]*s, m[ 2]*s, m[ 3]*s,
                m[ 4]*s, m[ 5]*s, m[ 6]*s, m[ 7]*s,
                m[ 8]*s, m[ 9]*s, m[10]*s, m[11]*s,
                m[12]*s, m[13]*s, m[14]*s, m[15]*s);
}

mat4 mat4::perspective(float32 fov, float32 aspect, float32 near, float32 far) {
    float32 radians = (PI / 180.0) * fov / 2.0;
    float32 yScale = 1.0/tan(radians);
    float32 nd = near - far;
    return mat4(yScale/aspect,     0.0f,                   0.0f,  0.0f,
                         0.0f,   yScale,                   0.0f,  0.0f,
                         0.0f,     0.0f,    (far+near)/nd, -1.0f,
                         0.0f,     0.0f, 2.0f*far*near/nd,  0.0f);
}

mat4 mat4::orthographic(float32 left, float32 right, float32 bottom, float32 top, float32 near, float32 far) {
    float32 w = right - left;
    float32 h = top - bottom;
    float32 d = far - near;
    return mat4(2.0f/w,   0.0f,    0.0f, -(left + right)/w,
                  0.0f, 2.0f/h,    0.0f, -(bottom + top)/h,
                  0.0f,   0.0f, -2.0f/d, -(near  +  far)/d,
                  0.0f,   0.0f,    0.0f,              1.0f);
}

mat4 mat4::orthographic(float32 w, float32 h, float32 d) {
    return mat4(2.0f/w,   0.0f,    0.0f, 0.0f,
                  0.0f, 2.0f/h,    0.0f, 0.0f,
                  0.0f,   0.0f, -2.0f/d, 0.0f,
                  0.0f,   0.0f,    0.0f, 1.0f);
}

mat4 mat4::translation(const vec3 &t) {
    return mat4(1.0, 0.0, 0.0, 0.0,
                0.0, 1.0, 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                t.x, t.y, t.z, 1.0);
}

mat4 mat4::scaling(const vec3 &s) { return scaling(vec4(s, 1.0)); }
mat4 mat4::scaling(const vec4 &s) {
    return mat4(s.x, 0.0, 0.0, 0.0,
                0.0, s.y, 0.0, 0.0,
                0.0, 0.0, s.z, 0.0,
                0.0, 0.0, 0.0, s.w);
}

mat4 mat4::xRotation(float32 a) {
    float32 s = sin(a);
    float32 c = cos(a);
    return mat4(1.0, 0.0, 0.0, 0.0,
                0.0,   c,  -s, 0.0,
                0.0,   s,   c, 0.0,
                0.0, 0.0, 0.0, 1.0);
}

mat4 mat4::yRotation(float32 a) {
    float32 s = sin(a);
    float32 c = cos(a);
    return mat4(  c, 0.0,   s, 0.0,
                0.0, 1.0, 0.0, 0.0,
                 -s, 0.0,   c, 0.0,
                0.0, 0.0, 0.0, 1.0);
}

mat4 mat4::zRotation(float32 a) {
    float32 s = sin(a);
    float32 c = cos(a);
    return mat4(  c,  -s, 0.0, 0.0,
                  s,   c, 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                0.0, 0.0, 0.0, 1.0);
}

mat4 mat4::rotation(const Quaternion &q) {
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
    return mat4(as + bs - cs - ds,         bc2 - ad2,         bd2 + ac2, 0.0f,
                        bc2 + ad2, as - bs + cs - ds,         cd2 - ab2, 0.0f,
                        bd2 - ac2,         cd2 + ab2, as - bs - cs + ds, 0.0f,
                             0.0f,              0.0f,              0.0f, 1.0f);
}

mat4 mat4::lookAt(const vec3 &direction, const vec3 &up) {
    vec3 f = normalize(direction);
    vec3 s = normalize(cross(f, up));
    vec3 u = normalize(cross(s, f));
    return mat4(  s.x,  u.x, -f.x, 0.0f,
                  s.y,  u.y, -f.y, 0.0f,
                  s.z,  u.z, -f.z, 0.0f,
                 0.0f, 0.0f, 0.0f, 1.0f);
}

mat4 operator*(const float32 s, const mat4& m) { return m*s; }


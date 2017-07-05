#include "Quaternion.h"

#include "Math.h"
#include "mat3.h"

using namespace Silexars::Math;
using namespace std;

Quaternion::Quaternion() {}
Quaternion::Quaternion(float32 a, float32 b, float32 c, float32 d) {
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
}
Quaternion::Quaternion(const Complex &ab, const Complex &cd) {
    this->a = ab.a;
    this->b = ab.b;
    this->c = cd.a;
    this->d = cd.b;
}
Quaternion::Quaternion(float32 angle, const vec3 &axis) {
    angle *= 0.5f;
    vec3 naxis = axis*sin(angle);
    a = cos(angle);
    b = naxis.x;
    c = naxis.y;
    d = naxis.z;
}

Quaternion::Quaternion(const vec3& eulerAngles) {
    vec3 e = eulerAngles * 0.5f;

    float32 sinp = sin(e.x);
    float32 siny = sin(e.y);
    float32 sinr = sin(e.z);
    float32 cosp = cos(e.x);
    float32 cosy = cos(e.y);
    float32 cosr = cos(e.z);

    a = cosr * cosp * cosy + sinr * sinp * siny;
    b = cosr * sinp * cosy + sinr * cosp * siny;
    c = cosr * cosp * siny - sinr * sinp * cosy;
    d = sinr * cosp * cosy - cosr * sinp * siny;
}

Quaternion Quaternion::operator-() const { return Quaternion(-a, -b, -c, -d); }

Quaternion Quaternion::operator+(const Quaternion& q) const { return Quaternion(a + q.a, b + q.b, c + q.c, d + q.d); }
Quaternion Quaternion::operator-(const Quaternion& q) const { return Quaternion(a + q.a, b + q.b, c + q.c, d + q.d); }
Quaternion Quaternion::operator*(const Quaternion& q) const { return Quaternion(a*q.a - b*q.b - c*q.c - d*q.d, a*q.b + b*q.a + c*q.d - d*q.c, a*q.c + c*q.a + d*q.b - b*q.d, a*q.d + d*q.a + b*q.c - c*q.b); }
//Quaternion Quaternion::operator/(const Quaternion& q) const { return Quaternion(); }

Quaternion Quaternion::operator+(const float32 s) const { return Quaternion(a + s, b, c, d); }
Quaternion Quaternion::operator-(const float32 s) const { return Quaternion(a - s, b, c, d); }
Quaternion Quaternion::operator*(const float32 s) const { return Quaternion(a * s, b * s, c * s, d * s); }
Quaternion Quaternion::operator/(const float32 s) const { return Quaternion(a / s, b / s, c / s, d / s); }

Quaternion operator+(const float32 s, const Quaternion& c) { return c + s; }
Quaternion operator-(const float32 s, const Quaternion& c) { return Quaternion(c.a - s, c.b, c.c, c.d ); }
Quaternion operator*(const float32 s, const Quaternion& c) { return c*s; }
Quaternion operator/(const float32 s, const Quaternion& c);

vec3 Quaternion::operator*(const vec3& v) const {
    vec3 q = vec3(b, c, d);
    vec3 t = cross(q, v)*2.0f;
    return v+cross(q, t)+t*a;
}
vec3 operator*(const vec3& v, const Quaternion& z) {
    vec3 q = vec3(z.b, z.c, z.d);
    vec3 t = cross(v, q) * 2.0f;
    return v+cross(t, q)+t*z.a;
}

void Quaternion::operator*=(float32 s) { a *= s; b *= s;c *= s; d *= s; }
void Quaternion::operator/=(float32 s) { a /= s; b /= s; c /= s; d /= s; }

void Quaternion::operator*=(const Quaternion& q) {
    float32 a = this->a;
    float32 b = this->b;
    float32 c = this->c;
    this->a = a*q.a - b*q.b - c*q.c - d*q.d;
    this->b = a*q.b + b*q.a + c*q.d - d*q.c;
    this->c = a*q.c + c*q.a + d*q.b - b*q.d;
    d = a*q.d + d*q.a + b*q.c - c*q.b;
}

void Quaternion::conjugate() { b = -b; c = -c; d = -d; }

#define NORMALIZATION_TOLERANCE 0.00000001f
void Quaternion::normalize() {
    float32 mag2 = a * a + b * b + c * c + d * d;
    if (abs(mag2) > NORMALIZATION_TOLERANCE && abs(mag2 - 1.0f) > NORMALIZATION_TOLERANCE)
        operator/=(sqrt(mag2));
}

// http://www.flipcode.com/documents/matrfaq.html#Q55 / http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/
Quaternion Quaternion::lookAt(const vec3 &direction, const vec3 &up) {
    mat3 m = mat3::lookAt(direction, up);
    #define m00 m.m[0]
    #define m10 m.m[1]
    #define m20 m.m[2]
    #define m01 m.m[3]
    #define m11 m.m[4]
    #define m21 m.m[5]
    #define m02 m.m[6]
    #define m12 m.m[7]
    #define m22 m.m[8]
    float32 qw, qx, qy, qz;

    float32 tr = m00 + m11 + m22;

    if (tr > 0) {
      float32 S = sqrt(tr+1.0) * 2; // S=4*qw
      qw = 0.25 * S;
      qx = (m21 - m12) / S;
      qy = (m02 - m20) / S;
      qz = (m10 - m01) / S;
    } else if ((m00 > m11)&(m00 > m22)) {
      float32 S = sqrt(1.0 + m00 - m11 - m22) * 2; // S=4*qx
      qw = (m21 - m12) / S;
      qx = 0.25 * S;
      qy = (m01 + m10) / S;
      qz = (m02 + m20) / S;
    } else if (m11 > m22) {
      float32 S = sqrt(1.0 + m11 - m00 - m22) * 2; // S=4*qy
      qw = (m02 - m20) / S;
      qx = (m01 + m10) / S;
      qy = 0.25 * S;
      qz = (m12 + m21) / S;
    } else {
      float32 S = sqrt(1.0 + m22 - m00 - m11) * 2; // S=4*qz
      qw = (m10 - m01) / S;
      qx = (m02 + m20) / S;
      qy = (m12 + m21) / S;
      qz = 0.25 * S;
    }

    return Quaternion(qw, qx, qy, qz);

    #undef m00
    #undef m01
    #undef m02
    #undef m10
    #undef m11
    #undef m12
    #undef m20
    #undef m21
    #undef m22
}

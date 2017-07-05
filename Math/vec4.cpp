#include "vec4.h"

using namespace Silexars::Math;

vec4::vec4() {}
vec4::vec4(float32 value) { x = y = z = w = value; }
vec4::vec4(float32 x, float32 y, float32 z, float32 w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

vec4::vec4(const vec2 &xy, float32 z, float32 w) {
    this->x = xy.x;
    this->y = xy.y;
    this->z = z;
    this->w = w;
}

vec4::vec4(const vec2 &xy, const vec2 &zw) {
    this->x = xy.x;
    this->y = xy.y;
    this->z = zw.x;
    this->w = zw.y;
}

vec4::vec4(const vec3 &xyz, float32 w) {
    this->x = xyz.x;
    this->y = xyz.y;
    this->z = xyz.z;
    this->w = w;
}

vec4::vec4(float32 x, const vec3 &yzw) {
    this->x = x;
    this->y = yzw.x;
    this->z = yzw.y;
    this->w = yzw.z;
}

vec4 vec4::operator+(float32 s) const { return vec4(x+s, y+s, z+s, w+s); }
vec4 vec4::operator-(float32 s) const { return vec4(x-s, y-s, z-s, w-s); }
vec4 vec4::operator*(float32 s) const { return vec4(x*s, y*s, z*s, w*s); }
vec4 vec4::operator/(float32 s) const { return vec4(x/s, y/s, z/s, w/s); }

vec4 vec4::operator+(const vec4& v) const { return vec4(x+v.x, y+v.y, z+v.z, w+v.w); }
vec4 vec4::operator-(const vec4& v) const { return vec4(x-v.x, y-v.y, z-v.z, w-v.w); }
vec4 vec4::operator*(const vec4& v) const { return vec4(x*v.x, y*v.y, z*v.z, w*v.w); }
vec4 vec4::operator/(const vec4& v) const { return vec4(x/v.x, y/v.y, z/v.z, w/v.w); }

void vec4::operator+=(float32 s) { x += s; y += s; z += s; w += s; }
void vec4::operator-=(float32 s) { x -= s; y -= s; z -= s; w -= s; }
void vec4::operator*=(float32 s) { x *= s; y *= s; z *= s; w *= s; }
void vec4::operator/=(float32 s) { x /= s; y /= s; z /= s; w /= s; }

void vec4::operator+=(const vec4& v) { x += v.x; y += v.y; z += v.z; w += v.w; }
void vec4::operator-=(const vec4& v) { x -= v.x; y -= v.y; z -= v.z; w -= v.w; }
void vec4::operator*=(const vec4& v) { x *= v.x; y *= v.y; z *= v.z; w *= v.w; }
void vec4::operator/=(const vec4& v) { x /= v.x; y /= v.y; z /= v.z; w /= v.w; }

bool vec4::operator==(const vec4& v) const { return x == v.x && y == v.y && z == v.z && w == v.w; }
bool vec4::operator!=(const vec4& v) const { return x != v.x || y != v.y || z != v.z || w != v.w; }

vec4 vec4::operator-() const { return vec4(-x, -y, -z, -w); }

vec4 operator*(const float32 s, const vec4& v) { return v*s; }

std::ostream& operator<<(std::ostream &os, const vec4& v) {
    os << '(' << v.x << ", " << v.y << ", " << v.z << ", " << v.w  << ")";
    return os;
}

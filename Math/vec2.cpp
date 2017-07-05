#include "vec2.h"

using namespace Silexars::Math;

vec2::vec2() {}
vec2::vec2(float32 value) { x = y = value; }
vec2::vec2(float32 x, float32 y) {
    this->x = x;
    this->y = y;
}

vec2 vec2::operator+(float32 s) const { return vec2(x+s, y+s); }
vec2 vec2::operator-(float32 s) const { return vec2(x-s, y-s); }
vec2 vec2::operator*(float32 s) const { return vec2(x*s, y*s); }
vec2 vec2::operator/(float32 s) const { return vec2(x/s, y/s); }

vec2 vec2::operator+(const vec2& v) const { return vec2(x+v.x, y+v.y); }
vec2 vec2::operator-(const vec2& v) const { return vec2(x-v.x, y-v.y); }
vec2 vec2::operator*(const vec2& v) const { return vec2(x*v.x, y*v.y); }
vec2 vec2::operator/(const vec2& v) const { return vec2(x/v.x, y/v.y); }

void vec2::operator+=(float32 s) { x += s; y += s; }
void vec2::operator-=(float32 s) { x -= s; y -= s; }
void vec2::operator*=(float32 s) { x *= s; y *= s; }
void vec2::operator/=(float32 s) { x /= s; y /= s; }

void vec2::operator+=(const vec2& v) { x += v.x; y += v.y; }
void vec2::operator-=(const vec2& v) { x -= v.x; y -= v.y; }
void vec2::operator*=(const vec2& v) { x *= v.x; y *= v.y; }
void vec2::operator/=(const vec2& v) { x /= v.x; y /= v.y; }

vec2 vec2::operator-() const { return vec2(-x, -y); }

vec2 operator*(const float32 s, const vec2& v) { return v*s; }

std::ostream& operator<<(std::ostream &os, const vec2& v) {
    os << '(' << v.x << ", " << v.y << ")";
    return os;
}

bool vec2::operator==(const vec2& v) const { return x == v.x && x == v.y; }
bool vec2::operator!=(const vec2& v) const { return x != v.x || y != v.y; }

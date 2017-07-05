#include "Complex.h"

using namespace Silexars::Math;

Complex::Complex() {}
Complex::Complex(float32 a, float32 b) {
    this->a = a;
    this->b = b;
}

Complex Complex::operator+(const Complex& c) const { return Complex(a+c.a, b+c.b); }
Complex Complex::operator-(const Complex& c) const { return Complex(a-c.a, b-c.b); }
Complex Complex::operator*(const Complex& c) const { return Complex(a*c.a - b*c.b, a*c.b + b*c.a); }
Complex Complex::operator/(const Complex& c) const { float32 d = c.a*c.a + c.b*c.b; return Complex((a*c.a + b*c.b)/d, (b*c.a - a*c.b)/d); }

Complex Complex::operator+(const float32 s) const { return Complex(a + s, b); }
Complex Complex::operator-(const float32 s) const { return Complex(a - s, b); }
Complex Complex::operator*(const float32 s) const { return Complex(a * s, b * s); }
Complex Complex::operator/(const float32 s) const { return Complex(a / s, b / b); }

void Complex::operator+=(const Complex& c) { a += c.a; b += c.b; }
void Complex::operator-=(const Complex& c) { a -= c.a; b -= c.b; }
void Complex::operator*=(const Complex& c) { float32 oa = a; a = a*c.a - b*c.b; b = oa*c.b + b*c.a; }
void Complex::operator/=(const Complex& c) { float32 d = c.a*c.a + c.b*c.b; float32 oa = a; a = (a*c.a + b*c.b)/d; b = (b*c.a - oa*c.b)/d; }

void Complex::operator+=(const float32 s) { a += s; }
void Complex::operator-=(const float32 s) { a -= s; }
void Complex::operator*=(const float32 s) { a *= s; b *= s; }
void Complex::operator/=(const float32 s) { a /= s; b /= s; }

Complex Complex::operator-() const { return Complex(-a, -b); }

void Complex::conjugate() { b = -b; }

Complex operator+(const float32 s, const Complex& c) { return Complex(s + c.a, c.b); }
Complex operator-(const float32 s, const Complex& c) { return Complex(s - c.a, -c.b); }
Complex operator*(const float32 s, const Complex& c) { return Complex(s * c.a, s * c.b); }
Complex operator/(const float32 s, const Complex& c) { return Complex(s, 0.0f)/Complex(c.a, c.b); }

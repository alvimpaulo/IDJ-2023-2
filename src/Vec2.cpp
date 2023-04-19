#include "Vec2.hpp"
#include <cmath>

Vec2::Vec2(float x, float y)
{
    this->x = x;
    this->y = y;
}

const Vec2 Vec2::operator+(const Vec2 &rhs)
{
    return Vec2(x + rhs.x, y + rhs.y);
}

const Vec2 Vec2::operator-(const Vec2 &rhs)
{
    return Vec2(x - rhs.x, y - rhs.y);
}

const Vec2 Vec2::operator*(float rhs)
{
    return Vec2(x * rhs, y * rhs);
}

Vec2 Vec2::Rotate(const Vec2 &p, float angle)
{
    float cs = std::cos(angle), sn = std::sin(angle);
    return Vec2(p.x * cs - p.y * sn, p.x * sn + p.y * cs);
}

float Vec2::Dot(const Vec2 &a, const Vec2 &b)
{
    return a.x * b.x + a.y * b.y;
}
float Vec2::Mag(const Vec2 &p){
    return std::sqrt(p.x * p.x + p.y * p.y);
}

Vec2 Vec2::getRotated(const float rad){
   float cs = std::cos(rad), sn = std::sin(rad);
    return Vec2(x * cs - y * sn, x * sn + y * cs);
}
#include "Vec2.hpp"
#include <cmath>


Vec2::Vec2(float x, float y)
{
    this->x = x;
    this->y = y;
}

const Vec2 Vec2::operator+(const Vec2 &rhs) const
{
    return Vec2(x + rhs.x, y + rhs.y);
}

const Vec2 Vec2::operator-(const Vec2 &rhs) const
{
    return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 &Vec2::operator-=(const Vec2 &a)
{
    this->x -= a.x;
    this->y -= a.y;
    return *this;
}

Vec2 &Vec2::operator+=(const Vec2 &a)
{
    this->x += a.x;
    this->y += a.y;
    return *this;
}

Vec2 Vec2::operator*(const float &num) const
{
    return Vec2(x * num, y * num);
}

Vec2 &Vec2::operator*=(const float &num)
{
    this->x *= num;
    this->y *= num;
    return *this;
}

Vec2 Vec2::RotateDeg(const Vec2 &p, float deg)
{
    float cs = std::cos(deg), sn = std::sin(deg);
    return Vec2(p.x * cs - p.y * sn, p.x * sn + p.y * cs);
}
Vec2 Vec2::RotateRad(const Vec2 &p, float rad)
{
    return Vec2::RotateDeg(p, (float) Vec2::deg2rad(rad));
}

float Vec2::Dot(const Vec2 &a, const Vec2 &b)
{
    return a.x * b.x + a.y * b.y;
}
float Vec2::Mag(const Vec2 &p)
{
    return std::sqrt(p.x * p.x + p.y * p.y);
}

Vec2 Vec2::Norm(const Vec2 &p){
    return Vec2((float) (p.x/(pow(p.x, 2) + pow(p.y, 2))), (float) (p.y/(pow(p.x, 2) + pow(p.y, 2))));
}

 Vec2 Vec2::GetRotatedRad(const float rad) const
{
    float cs = std::cos(rad), sn = std::sin(rad);
    return Vec2(x * cs - y * sn, x * sn + y * cs);
}

 Vec2 Vec2::GetRotatedDeg(const float deg) const
{
    return (this->GetRotatedRad((float) Vec2::deg2rad(deg)));
}

float Vec2::GetAngleRad(const Vec2 &a, const Vec2 &b)
{
    auto temp = Vec2(b.x - a.x, b.y - a.y);
    auto angle = atan2(temp.y, temp.x);
    return float(angle);
}

float Vec2::GetDistancePix(const Vec2 &a, const Vec2 &b)
{
    return (float)sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

double Vec2::rad2deg(double rad)
{
    return rad * (180 / PI);
}

double Vec2::deg2rad(double deg)
{
    return deg * (PI / 180);
}
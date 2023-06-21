#pragma once

class Vec2
{
private:
    /* data */
public:
    Vec2(float x = 0.0, float y = 0.0);

    float x;
    float y;

    static float Dot(const Vec2 &a, const Vec2 &b);
    static Vec2 RotateDeg(const Vec2 &p, float angle);
    static Vec2 Norm(const Vec2 &p);
    static float Mag(const Vec2 &p);
    static double rad2deg(double rad);
    static double deg2rad(double deg);

    static float GetAngleRad(const Vec2 &a, const Vec2 &b);
    static float GetDistancePix(const Vec2 &a, const Vec2 &b);
    const Vec2 GetRotatedRad(const float rad);

    const Vec2 operator+(const Vec2 &rhs);
    const Vec2 operator-(const Vec2 &rhs);
    Vec2 &operator+=(const Vec2 &a);
    Vec2 &operator-=(const Vec2 &a);
    Vec2 operator*(const float &num);
    Vec2 &operator*=(const float &num);
};
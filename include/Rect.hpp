#pragma once
#include <utility>
#include "Vec2.hpp"

class Rect
{
public:
    Rect( float x = 0.0, float y = 0.0, float w = 200.0, float h = 200.0);
    float x;
    float y;
    float w;
    float h;

    bool Contains(std::pair<float, float> pair);
    Vec2 GetCenter() const;
    void SetCenter(Rect r);
    void SetCenter(Vec2 r);
};

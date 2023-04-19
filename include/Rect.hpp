#pragma once
#include <utility>

class Rect
{
public:
    Rect( float x = 0.0, float y = 0.0, float w = 200.0, float h = 200.0);
    float x;
    float y;
    float w;
    float h;

    bool Contains(std::pair<float, float> pair);
};

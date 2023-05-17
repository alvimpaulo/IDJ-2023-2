#include "Rect.hpp"
#include <utility>

Rect::Rect(float x , float y , float w, float h)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

bool Rect::Contains(std::pair<float, float> pair){
    return (pair.first > x && pair.first < x+w) && (pair.second > y && pair.second < y+h);
}

Vec2 Rect::GetCenter() {
    Vec2 v;
    v.x = x + w/2;
    v.y = y + h/2;
    return v;
}

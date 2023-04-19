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

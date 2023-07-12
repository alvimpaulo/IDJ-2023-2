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

 Vec2 Rect::GetCenter() const{
    Vec2 v;
    v.x = x + w/2;
    v.y = y + h/2;
    return v;
}

void Rect::SetCenter(Rect r){

    auto newCenter = r.GetCenter();
    this->x = newCenter.x - this->w/2;
    this->y = newCenter.y - this->h/2;
}

void Rect::SetCenter(Vec2 v){

    this->x = v.x - this->w/2;
    this->y = v.y - this->h/2;
}



#pragma once
#include "Component.hpp"

class GreenBar : public Component
{
private:
    /* data */
public:
    GreenBar(GameObject & associated);
    void Update(float dt);
    void Render();
    void Shoot(Vec2 target);
    void NotifyCollision (GameObject& other );
    void setScale(double scale);
    double getScale();
};

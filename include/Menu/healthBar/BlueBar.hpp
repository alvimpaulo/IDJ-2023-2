#pragma once
#include "Component.hpp"

class BlueBar : public Component
{
private:
    /* data */
public:
    BlueBar(GameObject & associated);
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void Shoot(Vec2 target);
    void NotifyCollision (GameObject& other );
    void setScale(double scale);
    double getScale();
};

#pragma once
#include "Component.hpp"

class RedBar : public Component
{
private:
    /* data */
public:
    RedBar(GameObject & associated);
    void Update(float dt);
    void Render();
    void Shoot(Vec2 target);
    void NotifyCollision (GameObject& other );
};

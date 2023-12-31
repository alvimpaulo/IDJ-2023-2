#pragma once
#include "Component.hpp"

class OutlineBar : public Component
{
private:
    /* data */
public:
    OutlineBar(GameObject *associated);
    void Update(float dt);
    void Render();
    void Shoot(Vec2 target);
    void NotifyCollision (GameObject& other );
};

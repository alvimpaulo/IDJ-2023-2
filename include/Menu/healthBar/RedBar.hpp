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
    bool Is(std::string type);
    void Shoot(Vec2 target);
    void NotifyCollision (GameObject& other );
};

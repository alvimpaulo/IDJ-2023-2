#pragma once
#include <iostream>
#include "Component.hpp"
#include "GameObject.hpp"

class Face : public Component
{
private:
    int hitpoints;
public:
    Face(GameObject& associated);
    void Damage(int damage);
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    int GetHitpoints();
};

#pragma once
#include "Component.hpp"

class SkillButton : public Component
{
public:
    SkillButton(GameObject &associated);
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void Start();
    void NotifyCollision(GameObject &other);

    bool isSelected;
};

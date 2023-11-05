#pragma once
#include "Component.hpp"
#include "ActionMenu.hpp"
class SkillButton : public Component
{
private:
    ActionMenu *menu;

public:
    SkillButton(GameObject &associated, ActionMenu* menu);
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void Start();
    void NotifyCollision(GameObject &other);

    bool isHovered;
};

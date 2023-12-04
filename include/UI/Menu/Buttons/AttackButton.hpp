#pragma once
#include "Component.hpp"
#include "ActionMenu.hpp"

class AttackButton : public Component
{
private:
    ActionMenu *menu;

public:
    AttackButton(GameObject *associated, ActionMenu* menu);
    void Update(float dt);
    void Render();
    void Start();
    void NotifyCollision(GameObject &other);

    bool isHovered;
};

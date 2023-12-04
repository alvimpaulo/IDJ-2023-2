#pragma once
#include "Component.hpp"
#include "ActionMenu.hpp"

class DefendButton : public Component
{
private:
    ActionMenu *menu;

public:
    DefendButton(GameObject *associated, ActionMenu* menu);
    void Update(float dt);
    void Render();
    void Start();
    void NotifyCollision(GameObject &other);

    bool isHovered;
};

#pragma once
#include "Component.hpp"

class Button : public Component
{
public:
    enum ButtonType
    {
        ATTACK,
        DEFEND,
        SKILL
    };
    Button(GameObject &associated, ButtonType type);
    void Update(float dt);
    void Render();
    void Start();
    void NotifyCollision(GameObject &other);

    bool isSelected;
};

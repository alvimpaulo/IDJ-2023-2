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
    bool Is(std::string type);
    void Start();
    void NotifyCollision(GameObject &other);

    bool isSelected;
};

#pragma once
#include "Component.hpp"

class DefendButton : public Component
{
public:
    DefendButton(GameObject &associated);
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void Start();
    void NotifyCollision(GameObject &other);

    bool isSelected;
};

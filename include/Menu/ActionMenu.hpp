#pragma once
#include "Component.hpp"
#include "Game.hpp"

class ActionMenu : public Component
{

public:
    ActionMenu(GameObject &associated);

    void Update(float dt);
    void Render();
    void Start();

    int height = SCREEN_HEIGHT / 10;
    int width = SCREEN_WIDTH / 4;
};

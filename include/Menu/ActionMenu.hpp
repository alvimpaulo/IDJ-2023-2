#pragma once
#include "Component.hpp"
#include "Game.hpp"

class ActionMenu : public Component
{
private:
    bool isVisible;

public:
    ActionMenu(GameObject &associated);

    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void Start();

    int height = SCREEN_HEIGHT / 10;
    int width = SCREEN_WIDTH / 4;
    void setVisible(bool newState);
};

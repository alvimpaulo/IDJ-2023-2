#pragma once
#include "Component.hpp"
#include "Game.hpp"
#include "ActionMenuSelector.hpp"

class ActionMenu : public Component
{

public:
    ActionMenu(GameObject &associated);

    void Update(float dt);
    void Render();
    void Start();

    ActionMenuSelector* selector;
    std::vector<Component*> buttons;

    void setButtons(std::vector<Component*> buttons);
    void setSelector(ActionMenuSelector* selector);

    int height = SCREEN_HEIGHT / 10;
    int width = SCREEN_WIDTH / 4;

    int selectedActionIndex = 0;
};

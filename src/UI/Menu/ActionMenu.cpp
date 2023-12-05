#include "ActionMenu.hpp"
#include "Sprite.hpp"
#include "InputManager.hpp"
#include "BattleState.hpp"
#include <bits/stdc++.h>

ActionMenu::ActionMenu(GameObject *associated) : Component(associated, "ActionMenu")
{
    auto bgSprite = new Sprite(associated, "assets/img/Menu/actionMenu.png", 1, 1, 0, 255 / 3 * 2);
    bgSprite->setOpacity(255);
    associated->AddComponent(bgSprite);

    auto selectorObject = new GameObject();
    this->buttons = {nullptr, nullptr, nullptr};
    this->selector = nullptr;
    selectedActionIndex = 0;

}
void ActionMenu::Update(float dt)
{
    if (BattleState::GetInstance()->getSelectedCharacter())
    {
        setIsVisible(true);
        if (this->selector->getIsActionLocked() == false)
        {
            if (InputManager::GetInstance().KeyPress(RIGHT_ARROW_KEY))
            {
                selectedActionIndex = std::min(selectedActionIndex + 1, (int) buttons.size() - 1);
                selector->setAttached(buttons[selectedActionIndex]);
            }

            if (InputManager::GetInstance().KeyPress(LEFT_ARROW_KEY))
            {
                selectedActionIndex = std::max(selectedActionIndex - 1, 0);
                selector->setAttached(buttons[selectedActionIndex]);
            }

            if (InputManager::GetInstance().KeyPress(SDLK_SPACE))
            {
                selector->setIsActionLocked(true);
                BattleState::GetInstance()->setRound(BattleState::Round::PlayerAction);
            }
        } else {
             if (InputManager::GetInstance().KeyPress(SDLK_MINUS))
            {
                selector->setIsActionLocked(false);
                BattleState::GetInstance()->setRound(BattleState::Round::PlayerActionSelect);
            }
        }
    }
    else
    {
        setIsVisible(false);
    }
}
void ActionMenu::Render()
{
    if (this->getIsVisible())
    {
        associated->setBoxCenter(Vec2(SCREEN_WIDTH / 2, associated->getBox().h / 2));
    }
    else
    {
        associated->setBoxCenter(Vec2(-SCREEN_WIDTH, -SCREEN_HEIGHT));
    }
}
void ActionMenu::Start()
{
}

void ActionMenu::setButtons(std::vector<Component*> buttons){
    this->buttons = buttons;
}

void ActionMenu::setSelector(ActionMenuSelector* selector){
    this->selector = selector;
}

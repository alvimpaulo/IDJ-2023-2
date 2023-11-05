#include "ActionMenu.hpp"
#include "Sprite.hpp"
#include "InputManager.hpp"
#include "BattleState.hpp"

ActionMenu::ActionMenu(GameObject &associated) : Component(associated)
{
    auto bgSprite = new Sprite(associated, "/home/paulo/unb/IDJ-2/trab1/assets/img/Menu/actionMenu.png", 1, 1, 0, 255/3 * 2);
    bgSprite->setOpacity(255);
    associated.AddComponent(bgSprite);
}
void ActionMenu::Update(float dt)
{
    if(BattleState::GetInstance()->getSelectedCharacter()){
        setIsVisible(true);
    } else{
        setIsVisible(false);
    }
}
void ActionMenu::Render()
{
    if (this->getIsVisible())
    {
        associated.setBoxCenter(Vec2(SCREEN_WIDTH / 2, associated.getBox().h / 2));
    }
    else
    {
        associated.setBoxCenter(Vec2(-SCREEN_WIDTH, -SCREEN_HEIGHT));
    }
}
bool ActionMenu::Is(std::string type)
{
    return type == "ActionMenu";
}
void ActionMenu::Start()
{
}
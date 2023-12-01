#include "AttackButton.hpp"
#include "Sprite.hpp"
#include "Collider.hpp"
#include "Game.hpp"

AttackButton::AttackButton(GameObject &associated, ActionMenu *menu) : Component(associated, "AttackButton")
{
    Sprite *ptrSprite;
    ptrSprite = new Sprite(associated, "assets/img/Menu/buttons/swordButton.png");
    associated.setBoxCenter(Vec2(412, 16 + 8));
    associated.AddComponent(ptrSprite);

    isHovered = false;
    this->menu = menu;
}
void AttackButton::Update(float dt)
{
    this->setIsVisible(this->menu->getIsVisible());
}
void AttackButton::Render()
{
    if (this->getIsVisible())
    {
        auto menuBox = menu->associated.getScaledBox();
        auto myBox = associated.getScaledBox();
        associated.setBoxCenter(Vec2(menuBox.x + myBox.w / 2 + 10, myBox.h / 2 + 10));
    }
    else
    {
        associated.setBoxCenter(Vec2(-SCREEN_WIDTH, -SCREEN_HEIGHT));
    }
}
void AttackButton::Start()
{
}
void AttackButton::NotifyCollision(GameObject &other)
{
}

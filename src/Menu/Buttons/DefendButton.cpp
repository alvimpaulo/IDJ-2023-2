#include "DefendButton.hpp"
#include "Sprite.hpp"
#include "Collider.hpp"
#include "Game.hpp"

DefendButton::DefendButton(GameObject &associated, ActionMenu* menu) : Component(associated)
{
    Sprite *ptrSprite;
    ptrSprite = new Sprite(associated, "assets/img/Menu/buttons/shieldButton.png");
    associated.setBoxCenter(Vec2(512, 16 + 8));
    associated.AddComponent(ptrSprite);

    isHovered = false;
    this->menu = menu;
}
void DefendButton::Update(float dt)
{
    this->setIsVisible(this->menu->getIsVisible());
}
void DefendButton::Render()
{
    if (getIsVisible())
    {
        auto menuBox = menu->associated.getScaledBox();
        auto myBox = associated.getScaledBox();
        associated.setBoxCenter(Vec2(menuBox.x + menuBox.w/2, myBox.h / 2 + 10));
    }
    else
    {
        associated.setBoxCenter(Vec2(-SCREEN_WIDTH, -SCREEN_HEIGHT));
    }
}
bool DefendButton::Is(std::string type)
{
    return type == "DefendButton";
}
void DefendButton::Start()
{
}
void DefendButton::NotifyCollision(GameObject &other)
{
}

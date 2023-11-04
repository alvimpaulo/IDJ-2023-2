#include "DefendButton.hpp"
#include "Sprite.hpp"
#include "Collider.hpp"
#include "Game.hpp"

DefendButton::DefendButton(GameObject &associated) : Component(associated), isSelected(false)
{
    Sprite *ptrSprite;
    ptrSprite = new Sprite(associated, "assets/img/Menu/buttons/shieldButton.png");
        associated.setBoxCenter(Vec2(512, 16 + 8));
    associated.AddComponent(ptrSprite);

    isVisible = false;
    isSelected = false;
}
void DefendButton::Update(float dt)
{
    //  if (this->isVisible)
    // {
    //     associated.setBoxCenter(Vec2(SCREEN_WIDTH / 2, associated.box.h / 2));
    // }
    // else
    // {
    //     associated.setBoxCenter(Vec2(-SCREEN_WIDTH, -SCREEN_HEIGHT));
    // }
}
void DefendButton::Render()
{
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

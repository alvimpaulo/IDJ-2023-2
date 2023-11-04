#include "AttackButton.hpp"
#include "Sprite.hpp"
#include "Collider.hpp"
#include "Game.hpp"

AttackButton::AttackButton(GameObject &associated) : Component(associated), isSelected(false)
{
    Sprite *ptrSprite;
    ptrSprite = new Sprite(associated, "assets/img/Menu/buttons/swordButton.png");
    associated.setBoxCenter(Vec2(412, 16 + 8));
    associated.AddComponent(ptrSprite);

    isVisible = false;
    isSelected = false;
}
void AttackButton::Update(float dt)
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
void AttackButton::Render()
{
}
bool AttackButton::Is(std::string type)
{
    return type == "AttackButton";
}
void AttackButton::Start()
{
}
void AttackButton::NotifyCollision(GameObject &other)
{
}

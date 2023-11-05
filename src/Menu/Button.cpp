#include "Button.hpp"
#include "Sprite.hpp"
#include "Collider.hpp"
#include "Game.hpp"

Button::Button(GameObject &associated, ButtonType type) : Component(associated), isSelected(false)
{
    Sprite *ptrSprite;
    switch (type)
    {
    case ATTACK:
        ptrSprite = new Sprite(associated, "assets/img/Menu/buttons/swordButton.png");
        associated.setBoxCenter(Vec2(412, 16 + 8));
        break;
    case DEFEND:
        ptrSprite = new Sprite(associated, "assets/img/Menu/buttons/shieldButton.png");
        associated.setBoxCenter(Vec2(512, 16 + 8));
        break;
    case SKILL:
        ptrSprite = new Sprite(associated, "assets/img/Menu/buttons/skillButton.png");
        associated.setBoxCenter(Vec2(612, 16 + 8));
        break;
    default:
        break;
    }

    associated.AddComponent(ptrSprite);
    auto collider = new Collider(associated);
    associated.AddComponent(collider);
    isSelected = false;
}
void Button::Update(float dt)
{
}
void Button::Render()
{
    if (getIsVisible())
    {
        associated.setBoxCenter(Vec2(SCREEN_WIDTH / 2, associated.getScaledBox().h / 2));
    }
    else
    {
        associated.setBoxCenter(Vec2(-SCREEN_WIDTH, -SCREEN_HEIGHT));
    }
}
bool Button::Is(std::string type)
{
    return type == "Button";
}
void Button::Start()
{
}
void Button::NotifyCollision(GameObject &other)
{
}

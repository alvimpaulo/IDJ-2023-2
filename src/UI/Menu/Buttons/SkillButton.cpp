#include "SkillButton.hpp"
#include "Sprite.hpp"
#include "Collider.hpp"
#include "Game.hpp"

SkillButton::SkillButton(GameObject *associated, ActionMenu* menu) : Component(associated, "SkillButton")
{
    Sprite *ptrSprite;
    ptrSprite = new Sprite(associated, "assets/img/Menu/buttons/skillButton.png");
    associated->setBoxCenter(Vec2(612, 16 + 8));
    associated->AddComponent(ptrSprite);

    isHovered = false;
    this->menu = menu;
}
void SkillButton::Update(float dt)
{
    this->setIsVisible(this->menu->getIsVisible());
}
void SkillButton::Render()
{
    if (getIsVisible())
    {
        auto menuBox = menu->associated->getScaledBox();
        auto myBox = associated->getScaledBox();
        associated->setBoxCenter(Vec2((menuBox.x+menuBox.w) - (myBox.w/2) - 10, myBox.h / 2 + 10));
    }
    else
    {
        associated->setBoxCenter(Vec2(-SCREEN_WIDTH, -SCREEN_HEIGHT));
    }
}
void SkillButton::Start()
{
}
void SkillButton::NotifyCollision(GameObject &other)
{
}

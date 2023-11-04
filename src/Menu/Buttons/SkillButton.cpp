#include "SkillButton.hpp"
#include "Sprite.hpp"
#include "Collider.hpp"
#include "Game.hpp"

SkillButton::SkillButton(GameObject &associated) : Component(associated), isSelected(false)
{
    Sprite *ptrSprite;
    ptrSprite = new Sprite(associated, "assets/img/Menu/buttons/skillButton.png");
    associated.setBoxCenter(Vec2(612, 16 + 8));
    associated.AddComponent(ptrSprite);

    isVisible = false;
    isSelected = false;
}
void SkillButton::Update(float dt)
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
void SkillButton::Render()
{
}
bool SkillButton::Is(std::string type)
{
    return type == "SkillButton";
}
void SkillButton::Start()
{
}
void SkillButton::NotifyCollision(GameObject &other)
{
}

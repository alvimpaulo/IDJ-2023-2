#include "OutlineBar.hpp"
#include "Sprite.hpp"

OutlineBar::OutlineBar(GameObject &associated) : Component(associated)
{
    auto outlineSprite = new Sprite(associated, "assets/img/Menu/healthBar/outline.png");
    associated.AddComponent(outlineSprite);
}
void OutlineBar::Update(float dt)
{
}
void OutlineBar::Render()
{
}
bool OutlineBar::Is(std::string type)
{
    return type == "OutlineBar";
}
void OutlineBar::Shoot(Vec2 target)
{
}
void OutlineBar::NotifyCollision(GameObject &other)
{
}

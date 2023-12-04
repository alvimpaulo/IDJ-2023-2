#include "OutlineBar.hpp"
#include "Sprite.hpp"

OutlineBar::OutlineBar(GameObject *associated) : Component(associated, "OutlineBar")
{
    auto outlineSprite = new Sprite(associated, "assets/img/Menu/bars/outline.png");
    associated->AddComponent(outlineSprite);
}
void OutlineBar::Update(float dt)
{
}
void OutlineBar::Render()
{
}
void OutlineBar::Shoot(Vec2 target)
{
}
void OutlineBar::NotifyCollision(GameObject &other)
{
}

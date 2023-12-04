#include "RedBar.hpp"
#include "Sprite.hpp"

RedBar::RedBar(GameObject *associated) : Component(associated, "RedBar")
{
    auto redSprite = new Sprite(associated, "assets/img/Menu/bars/red.png");
    associated->AddComponent(redSprite);
}
void RedBar::Update(float dt)
{
}
void RedBar::Render()
{
}
void RedBar::Shoot(Vec2 target)
{
}
void RedBar::NotifyCollision(GameObject &other)
{
}
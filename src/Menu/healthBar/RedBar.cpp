#include "RedBar.hpp"
#include "Sprite.hpp"

RedBar::RedBar(GameObject &associated) : Component(associated)
{
    auto redSprite = new Sprite(associated, "assets/img/Menu/bars/red.png");
    associated.AddComponent(redSprite);
}
void RedBar::Update(float dt)
{
}
void RedBar::Render()
{
}
bool RedBar::Is(std::string type)
{
    return type == "RedBar";
}
void RedBar::Shoot(Vec2 target)
{
}
void RedBar::NotifyCollision(GameObject &other)
{
}
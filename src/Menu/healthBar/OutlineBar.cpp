#include "OutlineBar.hpp"
#include "Sprite.hpp"

<<<<<<< HEAD
OutlineBar::OutlineBar(GameObject &associated) : Component(associated, "OutlineBar")
=======
OutlineBar::OutlineBar(GameObject &associated, std::string type) : Component(associated, type)
>>>>>>> f7e9db92a33dd43d0d2e2e03888ea3940bf3f923
{
    auto outlineSprite = new Sprite(associated, "assets/img/Menu/bars/outline.png");
    associated.AddComponent(outlineSprite);
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

#include "RedBar.hpp"
#include "Sprite.hpp"

<<<<<<< HEAD
RedBar::RedBar(GameObject &associated) : Component(associated, "RedBar")
=======
RedBar::RedBar(GameObject &associated, std::string type) : Component(associated, type)
>>>>>>> f7e9db92a33dd43d0d2e2e03888ea3940bf3f923
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
void RedBar::Shoot(Vec2 target)
{
}
void RedBar::NotifyCollision(GameObject &other)
{
}
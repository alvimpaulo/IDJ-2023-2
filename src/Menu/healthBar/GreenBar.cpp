#include "GreenBar.hpp"
#include "Sprite.hpp"

<<<<<<< HEAD
GreenBar::GreenBar(GameObject &associated) : Component(associated, "GreenBar")
=======
GreenBar::GreenBar(GameObject &associated, std::string type) : Component(associated, type)
>>>>>>> f7e9db92a33dd43d0d2e2e03888ea3940bf3f923
{
    auto greenSprite = new Sprite(associated, "assets/img/Menu/bars/green.png");
    greenSprite->setScale(Vec2(1, 1));
    associated.AddComponent(greenSprite);
}
void GreenBar::Update(float dt)
{
}
void GreenBar::Render()
{
}
void GreenBar::Shoot(Vec2 target)
{
}
void GreenBar::NotifyCollision(GameObject &other)
{
}

void GreenBar::setScale(double percentage)
{
    // ATTENTION: Second element in array only because it was the second to be initialized on healthbar!!
    auto spritePtr = (Sprite *)associated.GetComponentArray("Sprite")[1]; 
    spritePtr->setScale(Vec2(std::max(std::min(percentage, 1.0), 0.0), 1));
}

double GreenBar::getScale()
{
    // ATTENTION: Second element in array only because it was the second to be initialized on healthbar!!!!
    auto spritePtr = (Sprite *)associated.GetComponentArray("Sprite")[1];
    return spritePtr->getScale().x;
}
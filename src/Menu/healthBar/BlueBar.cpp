#include "BlueBar.hpp"
#include "Sprite.hpp"

BlueBar::BlueBar(GameObject &associated) : Component(associated)
{
    auto blueSprite = new Sprite(associated, "assets/img/Menu/bars/blue.png");
    blueSprite->setScale(Vec2(1, 1));
    associated.AddComponent(blueSprite);
}
void BlueBar::Update(float dt)
{
}
void BlueBar::Render()
{
}
bool BlueBar::Is(std::string type)
{
    return type == "BlueBar";
}
void BlueBar::Shoot(Vec2 target)
{
}
void BlueBar::NotifyCollision(GameObject &other)
{
}

void BlueBar::setScale(double percentage)
{
    // ATTENTION: Second element in array only because it was the second to be initialized on healthbar!!
    auto spritePtr = (Sprite *)associated.GetComponentArray("Sprite")[1]; 
    spritePtr->setScale(Vec2(std::max(std::min(percentage, 1.0), 0.0), 1));
}

double BlueBar::getScale()
{
    // ATTENTION: Second element in array only because it was the second to be initialized on healthbar!!!!
    auto spritePtr = (Sprite *)associated.GetComponentArray("Sprite")[1];
    return spritePtr->getScale().x;
}
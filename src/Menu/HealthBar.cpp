#include "HealthBar.hpp"
#include "Sprite.hpp"
#include "OutlineBar.hpp"
#include "RedBar.hpp"
#include "GreenBar.hpp"
#include "Collider.hpp"
#include "Game.hpp"

HealthBar::HealthBar(GameObject &associated, EntityComponent &baseEntity) : Component(associated), masterEntity(baseEntity)
{
    auto outlineSprite = new Sprite(associated, "assets/img/Menu/bars/outline.png");
    auto spriteWidth = outlineSprite->getWidth();
    delete (outlineSprite);
    this->associated.setScale(Vec2((float)masterEntity.associated.getScaledBox().w / spriteWidth, (float)masterEntity.associated.getScaledBox().w / spriteWidth));

    auto redBar = new RedBar(associated);
    associated.AddComponent(redBar);

    auto greenBar = new GreenBar(associated);
    associated.AddComponent(greenBar);

    auto outlineBar = new OutlineBar(associated);
    associated.AddComponent(outlineBar);

    // auto collider = new Collider(associated);
    // associated.AddComponent(collider);
}
void HealthBar::Update(float dt)
{
    if (masterEntity.getIsIndicated())
    {
        this->setIsVisible(true);
        double greenScale = (double)masterEntity.getCurrentHp() / masterEntity.getMaxHp();
        auto greenBar = (GreenBar *)associated.GetComponent("GreenBar");
        greenBar->setScale(greenScale);
        auto barHeight = greenBar->associated.getScaledBox().h;

        auto masterBox = masterEntity.associated.getScaledBox();

        associated.setBoxX(masterBox.x);
        associated.setBoxY(masterBox.y - barHeight * 2 - 10);
    } else {
        this->setIsVisible(false);
    }
}
void HealthBar::Render()
{
    if(!getIsVisible()){
        associated.setBoxCenter(Vec2(-SCREEN_WIDTH, -SCREEN_HEIGHT));
    }
}
bool HealthBar::Is(std::string type)
{
    return type == "HealthBar";
}
void HealthBar::Shoot(Vec2 target)
{
}
void HealthBar::NotifyCollision(GameObject &other)
{
}
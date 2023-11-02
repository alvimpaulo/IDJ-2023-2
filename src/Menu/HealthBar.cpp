#include "HealthBar.hpp"
#include "Sprite.hpp"
#include "OutlineBar.hpp"
#include "RedBar.hpp"
#include "GreenBar.hpp"
#include "Collider.hpp"

HealthBar::HealthBar(GameObject &associated, EntityComponent& baseEntity) : Component(associated), masterEntity(baseEntity)
{
    auto outlineSprite = new Sprite(associated, "assets/img/Menu/healthBar/outline.png");
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
    double greenScale = (double) masterEntity.getCurrentHp() / masterEntity.getMaxHp();
    auto greenBar = (GreenBar *)associated.GetComponent("GreenBar");
    greenBar->setScale(greenScale);
    auto masterBox = masterEntity.associated.getBox();

    associated.setBoxX(masterBox.x);
    associated.setBoxY(masterBox.y - 10);
}
void HealthBar::Render()
{
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
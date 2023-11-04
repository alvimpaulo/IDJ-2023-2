#include "ManaBar.hpp"
#include "Sprite.hpp"
#include "OutlineBar.hpp"
#include "RedBar.hpp"
#include "BlueBar.hpp"
#include "Collider.hpp"

ManaBar::ManaBar(GameObject &associated, EntityComponent& baseEntity) : Component(associated), masterEntity(baseEntity)
{
    auto outlineSprite = new Sprite(associated, "assets/img/Menu/bars/outline.png");
    auto spriteWidth = outlineSprite->getWidth();
    delete (outlineSprite);
    this->associated.setScale(Vec2((float)masterEntity.associated.getScaledBox().w / spriteWidth, (float)masterEntity.associated.getScaledBox().w / spriteWidth));

    auto redBar = new RedBar(associated);
    associated.AddComponent(redBar);

    auto greenBar = new BlueBar(associated);
    associated.AddComponent(greenBar);

    auto outlineBar = new OutlineBar(associated);
    associated.AddComponent(outlineBar);

    // auto collider = new Collider(associated);
    // associated.AddComponent(collider);
}
void ManaBar::Update(float dt)
{
    double blueScale = (double) masterEntity.getCurrentMp() / masterEntity.getMaxMp();
    auto blueBar = (BlueBar *)associated.GetComponent("BlueBar");
    blueBar->setScale(blueScale);
    auto barHeight = blueBar->associated.getScaledBox().h;
    auto masterBox = masterEntity.associated.getScaledBox();

    associated.setBoxX(masterBox.x);
    associated.setBoxY(masterBox.y - barHeight - 10);
}
void ManaBar::Render()
{
}
bool ManaBar::Is(std::string type)
{
    return type == "ManaBar";
}
void ManaBar::Shoot(Vec2 target)
{
}
void ManaBar::NotifyCollision(GameObject &other)
{
}
#include "Minion.hpp"
#include "Sprite.hpp"
#include "Bullet.hpp"
#include "Game.hpp"


Minion::Minion(GameObject &associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0) : Component(associated)
{
    this->arc = arcOffsetDeg;
    this->alienCenter = alienCenter;

    auto minionSprite = new Sprite(associated, "assets/img/minion.png");

    associated.AddComponent(minionSprite);
}
void Minion::Update(float dt)
{

    const float ROT_SPEED = 0.1f; // deg
    const auto PIVOT_DIST = Vec2(200.0f, 0.0f);

    if (auto alienPtr = this->alienCenter.lock())
    {
        this->arc += std::fmod(ROT_SPEED * dt, 360.0l);
        auto pos = Vec2::RotateDeg(PIVOT_DIST, Vec2::deg2rad(arc));

        pos += alienPtr->box.GetCenter(); // move to alien position

        this->associated.box.SetCenter(pos);
    }
    else
    {
        this->associated.RequestDelete();
    }
}
void Minion::Render()
{
}
bool Minion::Is(std::string type)
{
    return type == "Minion";
}
void Minion::Shoot(Vec2 target)
{
    auto targetAngleRad = Vec2::GetAngleRad(this->associated.box.GetCenter(), target);
    // auto targetAngleDeg = Vec2::rad2deg(targetAngleRad);

    auto bulletObject = new GameObject();

    auto bullet = new Bullet(*bulletObject, targetAngleRad, 0.8, 10, 1200, "assets/img/minionbullet1.png");
    bulletObject->AddComponent(bullet);

    bulletObject->box.SetCenter(this->associated.box.GetCenter());

    auto bulletObj = Game::GetInstance().GetState().AddObject(bulletObject);
}

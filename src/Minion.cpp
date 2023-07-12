#include "Minion.hpp"
#include "Sprite.hpp"
#include "Bullet.hpp"
#include "Game.hpp"
#include <random>
#include "Collider.hpp"

Minion::Minion(GameObject &associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0) : Component(associated)
{
    this->arc = arcOffsetDeg;
    this->alienCenter = alienCenter;
    auto minionSprite = new Sprite(associated, "assets/img/minion.png");

    // Random scale
    std::random_device rd;                          // obtain a random number from hardware
    std::mt19937 gen(rd());                         // seed the generator
    std::uniform_real_distribution<> distr(1, 1.5); // define the range
    float minionScale = (float)distr(gen);
    minionSprite->SetScaleX(minionScale, minionScale);

    associated.AddComponent(minionSprite);

    auto collider = new Collider(associated);
    this->associated.AddComponent(collider);
}
void Minion::Update(float dt)
{

    const float ROT_SPEED = 0.1f; // deg
    const auto PIVOT_DIST = Vec2(200.0f, 0.0f);

    if (auto alienPtr = this->alienCenter.lock())
    {
        this->arc += (float)std::fmod(ROT_SPEED * dt, 360.0l);
        auto pos = Vec2::RotateDeg(PIVOT_DIST, (float)Vec2::deg2rad(arc));

        pos += alienPtr->box.GetCenter(); // move to alien position

        this->associated.box.SetCenter(pos);

        associated.angleDeg = (float)Vec2::rad2deg(Vec2::GetAngleRad(this->associated.box.GetCenter(), alienPtr->box.GetCenter()));
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

    auto bulletObject = std::make_shared<GameObject>();

    auto bullet = new Bullet(*bulletObject, targetAngleRad, 0.8f, 10, 1200, "assets/img/minionbullet2.png", 3, 1, true);
    bulletObject->AddComponent(bullet);

    bulletObject->box.SetCenter(this->associated.box.GetCenter());

    auto bulletObj = Game::GetInstance().GetState().AddObject(bulletObject);
}

void Minion::NotifyCollision(GameObject &other)
{
    if ((Bullet *)other.GetComponent("Bullet"))
    {
        // Notify alienCenter to take damage
        if (auto alienPtr = alienCenter.lock())
        {
            alienPtr->NotifyCollision(other);
        }
        else
        {
            std::cerr << "Colisão do minion não conseguiu acessar o alien" << std::endl;
        }
    }
}
#include "Penguin/Minion.hpp"
#include "Sprite.hpp"
#include "Penguin/Bullet.hpp"
#include "Game.hpp"
#include <random>
#include "Collider.hpp"

Minion::Minion(GameObject &associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0) : Component(associated)
{
    this->arc = arcOffsetDeg;
    this->alienCenter = alienCenter;
    auto minionSprite = new Sprite(associated, "assets/img/Penguin/minion.png");

    // Random scale
    std::random_device rd;                          // obtain a random number from hardware
    std::mt19937 gen(rd());                         // seed the generator
    std::uniform_real_distribution<> distr(1, 1.5); // define the range
    float minionScale = (float)distr(gen);
    minionSprite->SetScale(Vec2(minionScale, minionScale));

    associated.AddComponent(minionSprite);

    auto collider = new Collider(associated);
    this->associated.AddComponent(collider);
}
void Minion::Update(float dt)
{

    const float ROT_SPEED = 10; // deg
    const auto PIVOT_DIST = Vec2(200.0f, 0.0f);

    if (auto alienPtr = this->alienCenter.lock())
    {
        this->arc += (float)std::fmod(ROT_SPEED * dt, 360.0l);
        auto pos = Vec2::RotateDeg(PIVOT_DIST, (float)Vec2::deg2rad(arc));

        pos += alienPtr->getBox().GetCenter(); // move to alien position

        this->associated.setBoxCenter(pos);

        associated.angleDeg = (float)Vec2::rad2deg(Vec2::GetAngleRad(this->associated.getBox().GetCenter(), alienPtr->getBox().GetCenter()));
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
    auto targetAngleRad = Vec2::GetAngleRad(this->associated.getBox().GetCenter(), target);

    auto bulletObject = new GameObject();
    ;

    auto bullet = new Bullet(*bulletObject, targetAngleRad, 1000, 10, 1200, "assets/img/Penguin/minionbullet2.png", 3, 1, true);
    bulletObject->AddComponent(bullet);

    bulletObject->setBoxCenter(this->associated.getBox().GetCenter());

    auto bulletObj = Game::GetInstance().GetCurrentState()->AddObject(bulletObject);
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
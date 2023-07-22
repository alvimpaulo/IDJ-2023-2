#include "Sprite.hpp"
#include "Alien.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "Game.hpp"
#include "Minion.hpp"
#include <cstdlib>
#include <memory>
#include <limits>
#include "Collider.hpp"
#include "Bullet.hpp"
#include "Sound.hpp"
#include "PenguinBody.hpp"

int Alien::alienCount = 0;

Alien::Alien(GameObject &associated, int nMinions = 0) : Component(associated)
{
    this->hp = 10;
    this->speed = Vec2(0, 0);
    this->nMinions = nMinions;
    Alien::alienCount += 1;
    this->state = RESTING;
    restTimer = Timer();

    auto alienSprite = new Sprite(associated, "assets/img/alien.png");
    this->associated.AddComponent(alienSprite);

    auto collider = new Collider(associated);
    this->associated.AddComponent(collider);
}

Alien::~Alien()
{
    this->minionArray.clear();
}

void Alien::Start()
{
    float arcStep = 360.0f / (float)nMinions;
    float arc = 0.0f;

    std::weak_ptr<GameObject> alienPtr = Game::GetInstance().GetCurrentState()->GetObjectPtr(&associated);

    if (alienPtr.lock() != nullptr)
    {
        for (int i = 0; i < nMinions; i++)
        {
            auto minionObject = new GameObject();
            auto minion = new Minion(*minionObject, alienPtr, arc);
            minionObject->AddComponent(minion);
            auto wpMinionGO = Game::GetInstance().GetCurrentState()->AddObject(minionObject);
            minionArray.push_back(wpMinionGO);

            arc += arcStep;
        }
    }
    else
    {
        std::cout << "Erro ao tentar dar lock no ponteiro de alien." << std::endl;
    }
}

void Alien::Update(float dt)
{
    float alienCooldown = 2;

    if (state == RESTING)
    {
        restTimer.Update(dt);
        auto playerPtr = PenguinBody::player;
        if (playerPtr)
            destination = playerPtr->associated.box.GetCenter();
    }

    if (restTimer.Get() > alienCooldown)
    {
        auto playerPtr = PenguinBody::player;
        if (playerPtr)
        {

            float maxSpeed = 10000;
            auto accel = 2000;

            auto srcPos = this->associated.box.GetCenter();
            auto dstPos = destination;
            auto deltaPos = dstPos - srcPos;

            this->speed += Vec2::Norm(deltaPos) * accel * dt;
            this->speed.x = std::max(std::min(maxSpeed, speed.x), -maxSpeed);
            this->speed.y = std::max(std::min(maxSpeed, speed.y), -maxSpeed);

            auto stepPos = srcPos + this->speed;

            auto distance = Vec2::GetDistancePix(stepPos, destination);

            auto dstThreshold = 15.0f;

            if (abs(distance) < dstThreshold)
            {
                // Alien chegou no lugar nesse update
                this->speed.x = 0;
                this->speed.y = 0;

                this->associated.box.SetCenter(destination);

                state = RESTING;

                this->restTimer.Restart();

                // Shoot
                auto playerPos = PenguinBody::player->associated.box.GetCenter();
                int closestMinionIdx = 0;
                float closestMinionDist = std::numeric_limits<float>::infinity();
                for (int i = 0; i < nMinions; i++)
                {
                    if (auto minionLock = minionArray[i].lock())
                    {
                        auto minionPos = minionLock->box.GetCenter();
                        auto minionDist = Vec2::GetDistancePix(playerPos, minionPos);
                        if (minionDist <= closestMinionDist)
                        {
                            closestMinionIdx = i;
                            closestMinionDist = minionDist;
                        }
                    }
                }

                auto selectedMinion = this->minionArray[closestMinionIdx];
                if (auto minionLock = selectedMinion.lock())
                {
                    Minion *minionPtr = (Minion *)(minionLock->GetComponent("Minion"));
                    if (minionPtr == nullptr)
                    {
                        std::cerr << "Não foi possível converter o ponteiro de minion em alien" << std::endl;
                        return;
                    }
                    minionPtr->Shoot(playerPos);
                }
            }
            else
            {
                this->associated.box.x += this->speed.x;
                this->associated.box.y += this->speed.y;
                state = MOVING;
            }
        }
    }

    // rotate alien
    auto angle = 5 * dt;

    angle += associated.GetAngle();
    associated.SetAngle(angle);
}

void Alien::Render()
{
}

bool Alien::Is(std::string type)
{
    return type == "Alien";
}

void Alien::NotifyCollision(GameObject &other)
{
    auto bulletPtr = (Bullet *)(other.GetComponent("Bullet"));
    if (!bulletPtr)
        return;

    // Take damage
    if (bulletPtr->targetsPlayer == false)
        hp -= bulletPtr->GetDamage();

    if (hp <= 0)
    {
        associated.RequestDelete();

        // Explosion animation
        auto exploGO = new GameObject();
        exploGO->AddComponent(new Sprite(*exploGO, "assets/img/aliendeath.png", 4, 0.500, 2));
        auto exploSOund = new Sound(*exploGO, "assets/audio/boom.wav");
        exploGO->AddComponent(exploSOund);
        exploGO->box.SetCenter(associated.box.GetCenter());
        exploSOund->Play();
        Game::GetInstance().GetCurrentState()->AddObject(exploGO);
    }
}
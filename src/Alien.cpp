#include "Sprite.hpp"
#include "Alien.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "Game.hpp"
#include "Minion.hpp"
#include <cstdlib>
#include <memory>
#include <limits>

Alien::Alien(GameObject &associated, int nMinions = 0) : Component(associated)
{
    this->hp = 10;
    this->speed = Vec2(0, 0);
    this->nMinions = nMinions;

    auto alienSprite = new Sprite(associated, "assets/img/alien.png");
    this->associated.AddComponent(alienSprite);
}

Alien::~Alien()
{
    this->minionArray.clear();
}

void Alien::Start()
{
    float arcStep = 360.0f / (float) nMinions;
    float arc = 0.0f;

    std::weak_ptr<GameObject> alienPtr = Game::GetInstance().GetState().GetObjectPtr(&associated);

    if (alienPtr.lock() != nullptr)
    {
        for (int i = 0; i < nMinions; i++)
        {
            auto minionObject = new GameObject();
            auto minion = new Minion(*minionObject, alienPtr, arc);
            minionObject->AddComponent(minion);
            auto wpMinionGO = Game::GetInstance().GetState().AddObject(minionObject);
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
    InputManager &inputManager = InputManager::GetInstance();
    auto mouseX = inputManager.GetMouseX();
    auto mouseY = inputManager.GetMouseY();

    auto mouseRealX = (float)mouseX + Camera::pos.x;
    auto mouseRealY = (float)mouseY + Camera::pos.y;

    if (inputManager.MousePress(LEFT_MOUSE_BUTTON))
    { // Shoot
        taskQueue.emplace(Action::SHOOT, mouseRealX, mouseRealY);
    }
    if (inputManager.MousePress(RIGHT_MOUSE_BUTTON))
    { // Move
        taskQueue.emplace(Action::MOVE, mouseRealX, mouseRealY);
    }

    // Executar açoes pendentes
    if (taskQueue.empty() == false)
    {
        auto &task = taskQueue.front();

        if (task.type == Action::MOVE)
        {

            auto maxSpeed = 14.0f;
            auto accel = 2.0f;

            auto srcPos = this->associated.box.GetCenter();
            auto dstPos = task.pos;
            auto deltaPos = dstPos - srcPos;

            // auto angle = Vec2::GetAngle(dstPos, srcPos);

            this->speed += Vec2::Norm(deltaPos) * accel * dt;
            this->speed.x = std::max(std::min(maxSpeed, speed.x), -maxSpeed);
            this->speed.y = std::max(std::min(maxSpeed, speed.y), -maxSpeed);

            auto stepPos = srcPos + this->speed;

            auto distance = Vec2::GetDistancePix(stepPos, task.pos);

            auto dstThreshold = 15.0f;

            if (abs(distance) < dstThreshold)
            {
                // Alien chegou no lugar nesse update
                this->speed.x = 0;
                this->speed.y = 0;

                this->associated.box.SetCenter(task.pos);
                taskQueue.pop();
            }
            else
            {
                this->associated.box.x += this->speed.x;
                this->associated.box.y += this->speed.y;
            }
        }
        else if (task.type == Action::SHOOT)
        {
            int closestMinionIdx = 0;
            float closestMinionDist = std::numeric_limits<float>::infinity();
            for (int i = 0; i < nMinions; i++)
            {
                if (auto minionLock = minionArray[i].lock())
                {
                    auto minionPos = minionLock->box.GetCenter();
                    auto minionDist = Vec2::GetDistancePix(task.pos, minionPos);
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
                minionPtr->Shoot(task.pos);
            }
            taskQueue.pop();
        }
    }

    // rotate alien
    auto angle = -0.05 * dt;

    if (auto sprite = (Sprite *)(associated.GetComponent("Sprite")))
    {
        angle += sprite->GetAngle();
        sprite->SetAngle(angle);
    }
}

void Alien::Render()
{
}

bool Alien::Is(std::string type)
{
    return type == "Alien";
}

Alien::Action::Action(ActionType type, float x, float y)
{
    this->type = type;
    this->pos = Vec2(x, y);
}
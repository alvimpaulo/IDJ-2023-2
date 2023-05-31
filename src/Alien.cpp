#include "Sprite.hpp"
#include "Alien.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include <cstdlib>

Alien::Alien(GameObject &associated, int nMinions) : Component(associated)
{
    this->hp = 10;
    this->speed = Vec2(0, 0);
    this->minionArray = std::vector<std::weak_ptr<GameObject>>(nMinions);

    auto alienSprite = new Sprite(associated, "assets/img/alien.png");
    this->associated.AddComponent(alienSprite);
}

Alien::~Alien()
{
    this->minionArray.clear();
}

void Alien::Start()
{
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
            
            auto distance = Vec2::GetDistance(stepPos, task.pos);

            auto dstThreshold = 15.0f;

            if(abs(distance) < dstThreshold){
                //Alien chegou no lugar nesse update
                this->speed.x = 0;
                this->speed.y = 0;

                this->associated.box.SetCenter(task.pos);
                taskQueue.pop();
            } else {
                this->associated.box.x += this->speed.x;
                this->associated.box.y += this->speed.y;
            }

            
        }
        else if (task.type == Action::SHOOT)
        {
            taskQueue.pop();
        }
    }
}

void Alien::Render(){}

bool Alien::Is(std::string type){
    return type == "Alien";
}

Alien::Action::Action(ActionType type, float x, float y) {
    this->type = type;
    this->pos = Vec2(x, y);
}
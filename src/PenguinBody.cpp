#include "PenguinBody.hpp"
#include "Sprite.hpp"
#include "Game.hpp"
#include "PenguinCannon.hpp"
#include "InputManager.hpp"
#include "constants.hpp"
#include "Collider.hpp"
#include "Bullet.hpp"
#include "Camera.hpp"
#include "Sound.hpp"

PenguinBody *PenguinBody::player = nullptr;

PenguinBody::PenguinBody(GameObject &associated) : Component(associated)
{
    speed = {0.0f, 0.0f};

    linearSpeed = 0.0f;
    hp = 20;

    auto ptrSprite = new Sprite(associated, "assets/img/penguin.png");

    associated.AddComponent(ptrSprite);

    auto collider = new Collider(associated);
    this->associated.AddComponent(collider);

    player = this;
}

PenguinBody::~PenguinBody()
{
    player = nullptr;
}

void PenguinBody::Start()
{
    auto bodyPtr = Game::GetInstance().GetCurrentState()->GetObjectPtr(&associated);

    auto cannonGo = new GameObject();
    auto cannonPtr = new PenguinCannon(*cannonGo, bodyPtr);
    cannonGo->AddComponent(cannonPtr);

    this->pcannon = Game::GetInstance().GetCurrentState()->AddObject(cannonGo);
}
void PenguinBody::Update(float dt)
{
    InputManager &inputManager = InputManager::GetInstance();

    const float maxSpeed = 20;
    // const float friction = 1.0f;
    const float speedStep = 10;
    const float angleStep = 100;

    auto speedChange = 0.0f;
    auto angleChange = 0.0f;

    if (inputManager.IsKeyDown(SDLK_a))
    {
        // rotate left
        angleChange -= angleStep * dt;
    }
    if (inputManager.IsKeyDown(SDLK_d))
    {
        // rotate right
        angleChange += angleStep * dt;
    }

    if (inputManager.IsKeyDown(SDLK_w))
    {
        // increase speed
        speedChange += speedStep * dt;
    }
    if (inputManager.IsKeyDown(SDLK_s))
    {
        // decrease speed
        speedChange -= speedStep * dt;
    }

    associated.angleDeg += angleChange;
    associated.angleDeg = (float)std::fmod(associated.angleDeg, 360);

    auto rotatedCurrentSpeed = this->speed.GetRotatedDeg(angleChange);
    auto speedChangeRotated = Vec2(speedChange, 0).GetRotatedDeg(associated.angleDeg);

    speed = rotatedCurrentSpeed + speedChangeRotated;

    speed.x = std::max(std::min(speed.x, maxSpeed), -maxSpeed);
    speed.y = std::max(std::min(speed.y, maxSpeed), -maxSpeed);

    Vec2 dest = associated.box.GetCenter() + speed;

    dest.x = std::min(std::max(dest.x, 0.0f), 1408.0f);    
    dest.y = std::min(std::max(dest.y, 0.0f), 1280.0f);    


    associated.box.SetCenter(dest);

    if (hp <= 0)
    {
        if (auto cannon = this->pcannon.lock())
        {
            cannon->RequestDelete();
        }

        this->associated.RequestDelete();
    }
}
void PenguinBody::Render()
{
}
bool PenguinBody::Is(std::string type)
{
    return type == "PenguinBody";
}

void PenguinBody::NotifyCollision(GameObject &other)
{
    auto bulletPtr = (Bullet *)other.GetComponent("Bullet");
    if (!bulletPtr)
        return;

    if (bulletPtr->targetsPlayer)
    {
        hp -= bulletPtr->GetDamage();
    }

    if (hp <= 0)
    {
        associated.RequestDelete();

        // Explosion animation
        auto exploGO = new GameObject();
        exploGO->AddComponent(new Sprite(*exploGO, "assets/img/penguindeath.png", 5, 0.400, 2));
        auto exploSOund = new Sound(*exploGO, "assets/audio/boom.wav");
        exploGO->AddComponent(exploSOund);
        exploGO->box.SetCenter(associated.box.GetCenter());
        exploSOund->Play();
        Game::GetInstance().GetCurrentState()->AddObject(exploGO);

        Camera::Unfollow();

        
    
    }
}
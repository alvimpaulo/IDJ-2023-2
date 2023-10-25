#include "Penguin/PenguinCannon.hpp"
#include "Sprite.hpp"
#include "InputManager.hpp"
#include "Game.hpp"
#include "Camera.hpp"
#include "Penguin/Bullet.hpp"
#include "Collider.hpp"

PenguinCannon::PenguinCannon(GameObject &associated,
                             std::weak_ptr<GameObject>
                                 penguinBody) : Component(associated)
{
    // lastShootTime = 0.f;
    this->pbody = penguinBody;
    this->timerLastShot = Timer();

    associated.AddComponent(new Sprite(associated, "assets/img/Penguin/cubngun.png"));
    auto collider = new Collider(associated);
    this->associated.AddComponent(collider);
}
void PenguinCannon::Update(float dt)
{
    timerLastShot.Update(dt);
    auto bodyPtr = pbody.lock();
    if (!bodyPtr)
    {
        associated.RequestDelete();
        return;
    }

    InputManager &inputManager = InputManager::GetInstance();
    auto mousePos = Vec2((float)inputManager.GetMouseX(), (float)inputManager.GetMouseY());
    mousePos += Camera::pos;

    associated.box.SetCenter(bodyPtr->box.GetCenter());

    associated.angleDeg = (float)Vec2::rad2deg(Vec2::GetAngleRad(associated.box.GetCenter(), mousePos));

    if (inputManager.MousePress(LEFT_MOUSE_BUTTON))
    {
        Shoot();
    }
}
void PenguinCannon::Render()
{
}
bool PenguinCannon::Is(std::string type)
{
    return type == "PenguinCannon";
}
void PenguinCannon::Shoot()
{
    if (timerLastShot.Get() > 1)
    {
        auto bulletObject = new GameObject();

        auto bullet = new Bullet(*bulletObject, (float)Vec2::deg2rad(this->associated.angleDeg), 1000, 10, 1200, "assets/img/Penguin/minionbullet2.png", 3, 1, false);

        Vec2 startPos;
        if (auto bodyGO = pbody.lock())
        {

            if (auto spritePtr = (Sprite *)bodyGO->GetComponent("Sprite"))
            {
                startPos.x += (float)spritePtr->GetWidth() / 2;

                startPos = startPos.GetRotatedRad((float)Vec2::deg2rad(associated.angleDeg));

                startPos += associated.box.GetCenter();
            }
        }

        bulletObject->AddComponent(bullet);

        bulletObject->box.SetCenter(startPos);

        auto bulletObj = Game::GetInstance().GetCurrentState()->AddObject(bulletObject);

        timerLastShot.Restart();
    }

     
}

void PenguinCannon::NotifyCollision(GameObject &other)
{
    if ((Bullet *)other.GetComponent("Bullet"))
    {
        if (auto bodyPtr = pbody.lock())
        {
            bodyPtr->NotifyCollision(other);
        }
        else
        {
            std::cerr << "PenguinCannon::NotifyCollision não conseguiu acessar o body" << std::endl;
        }
    }
}
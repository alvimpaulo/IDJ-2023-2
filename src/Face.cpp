#include "Face.hpp"
#include "Sound.hpp"
#include "Component.hpp"
#include "GameObject.hpp"
#include <SDL2/SDL.h>
#include "Sprite.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"

Face::Face(GameObject &associated) : Component(associated)
{
    this->hitpoints = 30;
}
void Face::Damage(int damage)
{
    hitpoints = hitpoints - damage;

    if (hitpoints <= 0)
    {

        auto sound = (Sound *)associated.GetComponent("Sound");
        if (sound != nullptr)
        {
            sound->Play();
            // std::cout << "played dying face" << std::endl;
        }

        associated.RequestDelete();
    }
}
void Face::Update(float dt)
{
    if (InputManager::GetInstance().MousePress(SDL_BUTTON_LEFT))
    {
        auto mouseScreenX = InputManager::GetInstance().GetMouseX();
        auto mouseScreenY = InputManager::GetInstance().GetMouseY();

        auto mouseRealX = static_cast<float>(mouseScreenX) + Camera::pos.x;
        auto mouseRealY = static_cast<float>(mouseScreenY) + Camera::pos.y;

        if (this->associated.box.Contains({(float)mouseRealX, (float)mouseRealY}))
        {
            this->Damage(std::rand() % 10 + 10);
        }
    }
    if (associated.IsDead())
    {
        associated.RemoveComponent(this);
    }
}
void Face::Render()
{
}
bool Face::Is(std::string type)
{
    return type == "Face";
}

int Face::GetHitpoints()
{
    return this->hitpoints;
}
#include "Camera.hpp"
#include "InputManager.hpp"
#include <SDL2/SDL.h>
#include "Rect.hpp"
#include "Vec2.hpp"
#include "Game.hpp"

GameObject *Camera::focus = nullptr;
Vec2 Camera::pos = Vec2(0, 0);
Vec2 Camera::speed = Vec2(0, 0);

void Camera::Follow(GameObject *newFocus)
{
    Camera::focus = newFocus;
}

void Camera::Unfollow()
{
    Camera::focus = nullptr;
}

void Camera::Update(float dt)
{
    Rect screenArea(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (Camera::focus != nullptr)
    {
        auto focusCenter = focus->getBox().GetCenter();
        auto screenCenter = screenArea.GetCenter();

        pos = Vec2(-(screenCenter.x - focusCenter.x), -(screenCenter.y - focusCenter.y));
    }
    else
    {
        // if (InputManager::GetInstance().IsKeyDown(SDLK_DOWN))
        // {
        //     Camera::pos.y += 5;
        // }
        // if (InputManager::GetInstance().IsKeyDown(SDLK_UP))
        // {
        //     Camera::pos.y -= 5;
        // }

        // if (InputManager::GetInstance().IsKeyDown(SDLK_RIGHT))
        // {
        //     Camera::pos.x += 5;
        // }
        // if (InputManager::GetInstance().IsKeyDown(SDLK_LEFT))
        // {
        //     Camera::pos.x-= 5;
        // }

        // Camera::pos.x += Camera::speed.x * dt;
        // Camera::pos.y += Camera::speed.y * dt;
    }
}

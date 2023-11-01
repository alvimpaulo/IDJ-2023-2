#include "Collider.hpp"
#include <algorithm>
#include <SDL2/SDL.h>
#include "Camera.hpp"
#include "Game.hpp"

Collider::Collider(GameObject &associated, Vec2 scale, Vec2 offset) : Component(associated)
{
    this->scale = scale;
    this->offset = offset;
    this->box = associated.getBox();
}

void Collider::SetScale(Vec2 scale)
{
    this->scale = scale;
}

void Collider::SetOffset(Vec2 offset)
{
    this->offset = offset;
}

bool Collider::Is(std::string type) { return type == "Collider"; }

void Collider::Render()
{
#ifndef NDEBUG
    Vec2 center(box.GetCenter());
    SDL_Point points[5];

    Vec2 point = (Vec2(box.x, box.y) - center).GetRotatedRad(associated.angleDeg / (180 / PI)) + center - Camera::pos;
    points[0] = {(int)point.x, (int)point.y};
    points[4] = {(int)point.x, (int)point.y};

    point = (Vec2(box.x + box.w, box.y) - center).GetRotatedRad(associated.angleDeg / (180 / PI)) + center - Camera::pos;
    points[1] = {(int)point.x, (int)point.y};

    point = (Vec2(box.x + box.w, box.y + box.h) - center).GetRotatedRad(associated.angleDeg / (180 / PI)) + center - Camera::pos;
    points[2] = {(int)point.x, (int)point.y};

    point = (Vec2(box.x, box.y + box.h) - center).GetRotatedRad(associated.angleDeg / (180 / PI)) + center - Camera::pos;
    points[3] = {(int)point.x, (int)point.y};

    SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif
}

void Collider::Update(float dt)
{
    box = associated.getBox();
    box.w = box.w * scale.x;
    box.h = box.h * scale.y;

    auto center = associated.getBox().GetCenter();
    center += offset;

    // box.SetCenter(center);
}

bool Collider::IsColliding(const Rect &a, const Rect &b, const float &angleOfA, const float &angleOfB)
{
    Vec2 A[] = {Vec2(a.x, a.y + a.h),
                Vec2(a.x + a.w, a.y + a.h),
                Vec2(a.x + a.w, a.y),
                Vec2(a.x, a.y)};
    Vec2 B[] = {Vec2(b.x, b.y + b.h),
                Vec2(b.x + b.w, b.y + b.h),
                Vec2(b.x + b.w, b.y),
                Vec2(b.x, b.y)};

    for (auto &v : A)
    {
        v = Vec2::RotateDeg(v - a.GetCenter(), angleOfA) + a.GetCenter();
    }

    for (auto &v : B)
    {
        v = Vec2::RotateDeg(v - b.GetCenter(), angleOfB) + b.GetCenter();
    }

    Vec2 axes[] = {Vec2::Norm(A[0] - A[1]), Vec2::Norm(A[1] - A[2]), Vec2::Norm(B[0] - B[1]), Vec2::Norm(B[1] - B[2])};

    for (auto &axis : axes)
    {
        float P[4];

        for (int i = 0; i < 4; ++i)
            P[i] = Vec2::Dot(A[i], axis);

        float minA = *std::min_element(P, P + 4);
        float maxA = *std::max_element(P, P + 4);

        for (int i = 0; i < 4; ++i)
            P[i] = Vec2::Dot(B[i], axis);

        float minB = *std::min_element(P, P + 4);
        float maxB = *std::max_element(P, P + 4);

        if (maxA < minB || minA > maxB)
            return false;
    }

    return true;
}

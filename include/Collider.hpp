#pragma once
#include "Component.hpp"
#include "Vec2.hpp"

class Collider : public Component
{
private:
    Vec2 offset;

public:
    Collider(GameObject *associated, Vec2 scale = {1, 1}, Vec2 offset = {0, 0});

    void SetOffset(Vec2 offset);

    void Update(float dt) override;
    void Render() override;

    static bool IsColliding(const Rect &a, const Rect &b, const float &angleOfA, const float &angleOfB);

    Rect box;
};
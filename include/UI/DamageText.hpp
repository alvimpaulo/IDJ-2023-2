#pragma once
#include "Component.hpp"
#include "Text.hpp"

class DamageText : public Component
{
private:
    int damage;
    Vec2 currentLocation;
    Vec2 startLocation;
    Vec2 endLocation;
    float timeElapsed;
    float duration;
    Text *textObject;

public:
    DamageText(GameObject *associated, int damage,
               Vec2 startLocation,
               Vec2 endLocation,
               float duration);
    ~DamageText();
    void Update(float dt) override;
    void Render() override;
};

#pragma once
#include "Component.hpp"
#include "Text.hpp"

class HealText : public Component
{
private:
    int heal;
    Vec2 currentLocation;
    Vec2 startLocation;
    Vec2 endLocation;
    float timeElapsed;
    float duration;
    Text *textObject;

public:
    HealText(GameObject *associated, int heal,
               Vec2 startLocation,
               Vec2 endLocation,
               float duration);
    ~HealText();
    void Update(float dt) override;
    void Render() override;
};

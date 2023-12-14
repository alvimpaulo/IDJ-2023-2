#pragma once
#include "Component.hpp"
#include "Text.hpp"

class MpLostText : public Component
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
    MpLostText(GameObject *associated, int damage,
               Vec2 startLocation,
               Vec2 endLocation,
               float duration);
    ~MpLostText();
    void Update(float dt) override;
    void Render() override;
};

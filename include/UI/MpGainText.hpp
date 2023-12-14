#pragma once
#include "Component.hpp"
#include "Text.hpp"

class MpGainText : public Component
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
    MpGainText(GameObject *associated, int damage,
               Vec2 startLocation,
               Vec2 endLocation,
               float duration);
    ~MpGainText();
    void Update(float dt) override;
    void Render() override;
};

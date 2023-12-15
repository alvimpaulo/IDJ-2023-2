#pragma once
#include "Component.hpp"
#include "Text.hpp"

class BlinkingText : public Component
{
private:
    int opacity;
    Vec2 location;
    float timeElapsed;
    float duration;
    Text *textObject;
    bool isFading;
    std::string text;

public:
    BlinkingText(GameObject *associated,
               Vec2 location,
               float duration, std::string text);
               
    void Update(float dt) override;
    void Render() override;
};

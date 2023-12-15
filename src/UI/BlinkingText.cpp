#include "BlinkingText.hpp"
#include "bits/stdc++.h"
#include "SDL2/SDL_mixer.h"
#include "Game.hpp"

BlinkingText::BlinkingText(GameObject *associated, Vec2 location, float duration, std::string text) : Component(associated, "BlinkingText")
{
    this->opacity = 0;
    this->location = location;
    this->duration = duration;
    this->timeElapsed = 0;
    this->isFading = false;
    this->text = text;

    // Text
    SDL_Color textColor = {255, 255, 255, (Uint8)opacity};
    this->textObject = new Text(associated, "assets/font/SpaceMono-Bold.ttf", 26, Text::BLENDED, text, textColor);
    associated->AddComponent(textObject);
}

void BlinkingText::Update(float dt)
{
    this->associated->setBoxX(this->location.x);
    this->associated->setBoxY(this->location.y);

    timeElapsed += dt;
    if (timeElapsed > duration)
    {
        timeElapsed = 0;
    }

    auto opacityIncrement = (255 / (duration / 2)) * dt;
    if (isFading)
    {
        opacity -= opacityIncrement;
    }
    else
    {
        opacity += opacityIncrement;
    }

    if (opacity < 1)
    {
        isFading = false;
        opacity = 1;
    }
    else if (opacity > 255)
    {
        isFading = true;
        opacity = 255;
    }

    
}

void BlinkingText::Render()
{
    // std::cout << opacity << std::endl;
    if (this->textObject != nullptr)
    {
        textObject->SetColor({textObject->getColor().r, textObject->getColor().g, textObject->getColor().b, (Uint8)opacity});
    }
    else
    {
        // Text
        SDL_Color textColor = {255, 255, 255, (Uint8)opacity};
        this->textObject = new Text(associated, "assets/font/SpaceMono-Bold.ttf", 26, Text::BLENDED, text, textColor);
        associated->AddComponent(textObject);
    }
}

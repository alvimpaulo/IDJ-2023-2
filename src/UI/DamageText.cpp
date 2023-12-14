
#include "DamageText.hpp"

DamageText::DamageText(GameObject *associated, int damage,
                       Vec2 startLocation, Vec2 endLocation,
                       float duration) : Component(associated, "DamageText")
{
    this->damage = damage;
    this->startLocation = startLocation;
    this->currentLocation = startLocation;
    this->endLocation = endLocation;
    this->duration = duration;
    this->timeElapsed = 0;

    // Text
    SDL_Color textColor = {255,255,51, 0xff};
    this->textObject = new Text(associated, "assets/font/Enchanted Land DEMO.otf", 56, Text::BLENDED, std::to_string(damage), textColor);
    associated->AddComponent(textObject);
}

DamageText::~DamageText()
{
}

void DamageText::Update(float dt)
{
    timeElapsed += dt;
    auto distancePerSecondX = (startLocation.x - endLocation.x) / duration;
    auto distancePerSecondY = (startLocation.y - endLocation.y) / duration;

    currentLocation = startLocation + Vec2(distancePerSecondX * timeElapsed, distancePerSecondY * timeElapsed);


    this->associated->setBoxCenter(currentLocation);

    if(timeElapsed >= duration){
        associated->RequestDelete();
    }
}

void DamageText::Render()
{
}

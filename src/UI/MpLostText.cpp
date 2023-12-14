
#include "MpLostText.hpp"

MpLostText::MpLostText(GameObject *associated, int damage,
                       Vec2 startLocation, Vec2 endLocation,
                       float duration) : Component(associated, "MpLostText")
{
    this->damage = damage;
    this->startLocation = startLocation;
    this->currentLocation = startLocation;
    this->endLocation = endLocation;
    this->duration = duration;
    this->timeElapsed = 0;

    // Text
    SDL_Color textColor = {93, 63, 211, 0xff};
    this->textObject = new Text(associated, "assets/font/Enchanted Land DEMO.otf", 56, Text::BLENDED, std::to_string(damage), textColor);
    associated->AddComponent(textObject);
}

MpLostText::~MpLostText()
{
}

void MpLostText::Update(float dt)
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

void MpLostText::Render()
{
}

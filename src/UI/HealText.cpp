
#include "HealText.hpp"

HealText::HealText(GameObject *associated, int heal,
                       Vec2 startLocation, Vec2 endLocation,
                       float duration) : Component(associated, "HealText")
{
    this->heal = heal;
    this->startLocation = startLocation;
    this->currentLocation = startLocation;
    this->endLocation = endLocation;
    this->duration = duration;
    this->timeElapsed = 0;

    // Text
    SDL_Color textColor = {124, 252, 0, 0xff};
    this->textObject = new Text(associated, "assets/font/Enchanted Land DEMO.otf", 56, Text::BLENDED, std::to_string(heal), textColor);
    associated->AddComponent(textObject);
}

HealText::~HealText()
{
}

void HealText::Update(float dt)
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

void HealText::Render()
{
}

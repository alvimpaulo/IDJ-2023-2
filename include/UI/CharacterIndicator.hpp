#pragma once
#include "Component.hpp"
#include "Entities/Entity.hpp"

class CharacterIndicator : public Component
{
    enum animationDirection
    {
        UP,
        DOWN
    };

private:
    EntityComponent *attached;
    double offset;
    animationDirection direction;
    bool isCharacterLocked;

public:
    CharacterIndicator(GameObject &associated, EntityComponent *selected);
    void Update(float dt);
    void Render();
    void Start();
    void setAttached(EntityComponent *newEntity);
    bool getIsCharacterLocked();
    void setIsCharacterLocked(bool newState);
};

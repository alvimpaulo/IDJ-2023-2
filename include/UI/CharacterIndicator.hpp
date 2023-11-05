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

public:
    CharacterIndicator(GameObject &associated, EntityComponent *selected);
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void Start();
    void setAttached(EntityComponent *newEntity);
};

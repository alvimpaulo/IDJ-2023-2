#pragma once
#include "Component.hpp"
#include "Entities/Entity.hpp"

class ManaBar : public Component
{
private:
    EntityComponent* masterEntity;

public:
    ManaBar(GameObject *associated, EntityComponent* baseEntity);
    void Update(float dt);
    void Render();
    void Shoot(Vec2 target);
    void NotifyCollision(GameObject &other);
    EntityComponent* getMasterEntity();
};
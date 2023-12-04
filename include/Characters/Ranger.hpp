#pragma once
#include "Component.hpp"
#include "Entities/Entity.hpp"
class Ranger : public EntityComponent
{
public:
    Ranger(GameObject *associated, int currentHp, int maxHp, int maxMp, int currentMp, int strength, int wisdom, int dexterity, int agility, int aggro, Sprite* idleSprite);
    ~Ranger();
    void Start();
    void Update(float dt);
    void Render();
    void NotifyCollision(GameObject &other);

private:
    Vec2 speed;
    float linearSpeed;
    float angle;
};

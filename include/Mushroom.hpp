#pragma once
#include "Vec2.hpp"
#include <string>
#include "Component.hpp"
#include "Timer.hpp"
#include "Entities/Entity.hpp"

class Mushroom : public EntityComponent
{
private:
    enum MushroomState
    {
        MOVING,
        RESTING
    };

public:
    Mushroom(GameObject &associated, int currentHp,
             int maxHp,

             int maxMp,
             int currentMp,

             int strength,
             int wisdom,
             int dexterity,
             int agility,

             int aggro);
    ~Mushroom();
    void Start() override;
    void Update(float dt) override;
    void Render() override;
    void NotifyCollision(GameObject &other) override;
};

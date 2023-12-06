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

    void physicalAttackStart(EntityComponent* target) override;
    void physicalAttackEnd(EntityComponent* target) override;

public:
    Mushroom(GameObject *associated, int currentHp,
             int maxHp,

             int maxMp,
             int currentMp,

             int strength,
             int wisdom,
             int dexterity,
             int agility,

             int aggro, Sprite *idleSprite);
    ~Mushroom();
    void Start() override;
    void Update(float dt) override;
    void Render() override;
    void NotifyCollision(GameObject &other) override;
    void useSkill(EntityComponent *target) override;
    void defend() override;
    void physicalAttack(EntityComponent *target) override;

    static Sprite* CreateIdleSprite(GameObject* associated);
    static Sprite* CreateRunSprite(GameObject* associated);
    static Sprite* CreateRunBackSprite(GameObject* associated);
};

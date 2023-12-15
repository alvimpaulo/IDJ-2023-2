#pragma once
#include "Vec2.hpp"
#include <string>
#include "Component.hpp"
#include "Timer.hpp"
#include "Entities/Entity.hpp"

class Porco : public EntityComponent
{
private:
    enum PorcoState
    {
        MOVING,
        RESTING
    };

    void physicalAttackStart(EntityComponent *target) override;
    void physicalAttackEnd(EntityComponent *target) override;
    void rhythmAttackStart(EntityComponent *target) override;
    void rhythmAttackEnd(EntityComponent *target) override;

public:
    Porco(GameObject *associated, int currentHp,
          int maxHp,

          int maxMp,
          int currentMp,

          int strength,
          int wisdom,
          int dexterity,
          int agility,

          int aggro, Sprite *idleSprite);
    ~Porco();
    void Start() override;
    void Update(float dt) override;
    void Render() override;
    void NotifyCollision(GameObject &other) override;
    void useSkill(EntityComponent *target) override;
    void defend() override;
    void physicalAttack(EntityComponent *target) override;
    void rhythmAttack(EntityComponent *target) override;

    static Sprite *CreateIdleSprite(GameObject *associated);
    static Sprite *CreateRunSprite(GameObject *associated);
    static Sprite *CreateRunBackSprite(GameObject *associated);
    static Sprite *CreateAttackSprite(GameObject *associated);
    static Sprite *CreateAttackBackSprite(GameObject *associated);
};

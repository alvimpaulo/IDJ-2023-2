#pragma once
#include "Component.hpp"
#include "Entities/Entity.hpp"
class Bargudin : public EntityComponent
{
public:
    Bargudin(GameObject *associated, int currentHp,
            int maxHp,

            int maxMp,
            int currentMp,

            int strength,
            int wisdom,
            int dexterity,
            int agility,

            int aggro, Sprite *idleSprite);
    ~Bargudin();
    void Start() override;
    void Update(float dt) override;
    void Render() override;
    void NotifyCollision(GameObject &other) override;
    void useSkill(EntityComponent *target) override;
    void defend() override;
    void physicalAttack(EntityComponent *target) override;
    void rhythmAttack(EntityComponent* target) override;

    static Sprite* CreateIdleSprite(GameObject* associated);
    static Sprite* CreateRunSprite(GameObject* associated);
    static Sprite* CreateRunBackSprite(GameObject* associated);
    static Sprite* CreateAttackSprite(GameObject* associated);
    static Sprite* CreateAttackBackSprite(GameObject* associated);

private:
    Vec2 speed;
    float linearSpeed;
    float angle;

    void physicalAttackStart(EntityComponent* target) override;
    void physicalAttackEnd(EntityComponent* target) override;

    void rhythmAttackStart(EntityComponent* target) override;
    void rhythmAttackEnd(EntityComponent* target) override;
};

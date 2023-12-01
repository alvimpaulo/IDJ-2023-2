#pragma once
#include "Component.hpp"

class EntityComponent : public Component
{
protected:
    int currentHp;
    int maxHp;

    int maxMp;
    int currentMp;

    int strength;
    int wisdom;
    int dexterity;
    int agility;

    int aggro;
    bool isIndicated;

    EntityComponent *target;

public:
    EntityComponent(GameObject &associated, std::string type, int currentHp,
                    int maxHp,

                    int maxMp,
                    int currentMp,

                    int strength,
                    int wisdom,
                    int dexterity,
                    int agility,

                    int aggro, bool isIndicated, Vec2 IdlePosition);
    void virtual Update(float dt) = 0;
    void virtual Render() = 0;
    void virtual Start() = 0;
    int getCurrentHp();
    int getMaxHp();
    int getCurrentMp();
    int getMaxMp();
    int getStrength();
    int getWisdom();
    int getDexterity();
    int getAgility();
    int getAggro();
    void startPhysicalAttack(EntityComponent *target);
    void useSkill(EntityComponent *target);
    void defend();

    void loseHp(int amount);
    void gainHp(int amount);

    void loseMp(int amount);
    void gainMp(int amount);

    bool getIsIndicated();
    void setIsIndicated(bool newState);

    bool isIdle;
    Vec2 IdlePosition;

    // Animations
    int attackAnimationFrames;
    int currentAnimationFrame;
    bool isOnAnimation;
    bool hasAttackFinished;

    // Attack
    void setTarget(EntityComponent *newTarget);
};

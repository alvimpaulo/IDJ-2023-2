#pragma once
#include "Component.hpp"
#include "Animation/Animation.hpp"

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
    Animation *currentAnimation;
    int rhythmAttackCount;

public:
    EntityComponent(GameObject *associated, std::string type, int currentHp,
                    int maxHp,

                    int maxMp,
                    int currentMp,

                    int strength,
                    int wisdom,
                    int dexterity,
                    int agility,

                    int aggro, bool isSelected, Vec2 IdlePosition, Sprite *idleSprite);
    // void virtual ~EntityComponent() = 0;
    void virtual Update(float dt);
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
    virtual void useSkill(EntityComponent *target) = 0;
    virtual void defend() = 0;

    virtual void physicalAttack(EntityComponent *target) = 0;
    virtual void rhythmAttack(EntityComponent *target) = 0;

     virtual void physicalAttackStart(EntityComponent *target) = 0;
    virtual void physicalAttackEnd(EntityComponent *target) = 0;
    virtual void rhythmAttackStart(EntityComponent* target) = 0;
    virtual void rhythmAttackEnd(EntityComponent* target) = 0;

    void loseHp(int amount);
    void gainHp(int amount);

    void loseMp(int amount);
    void gainMp(int amount);

    bool getIsIndicated();
    void setIsIndicated(bool newState);

    bool isIdle;
    Vec2 IdlePosition;

    // Animations

    void setNewAnimation(Animation *newAnimation);
    Animation *getCurrentAnimation() const { return currentAnimation; }

    std::mt19937 generator;


};

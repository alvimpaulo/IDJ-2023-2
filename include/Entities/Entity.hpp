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

public:
    EntityComponent(GameObject *associated, std::string type, int currentHp,
                    int maxHp,

                    int maxMp,
                    int currentMp,

                    int strength,
                    int wisdom,
                    int dexterity,
                    int agility,

                    int aggro, bool isSelected, Vec2 IdlePosition, Sprite *idleSprite,
                    Sprite *runSprite,Sprite *runBackSprite, Sprite *attackSprite, Sprite *criticalSprite);
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
    void useSkill(EntityComponent *target);
    void defend();
    void physicalAttack(EntityComponent *target);

    void loseHp(int amount);
    void gainHp(int amount);

    void loseMp(int amount);
    void gainMp(int amount);

    bool getIsIndicated();
    void setIsIndicated(bool newState);

    bool isIdle;
    Vec2 IdlePosition;

    // Animations
    std::deque<Animation *> animations;
    void goToNextAnimation();

    Sprite* idleSprite;
    Sprite* runSprite;
    Sprite* runBackSprite;
    Sprite* attackSprite;
    Sprite* criticalSprite;
    
};

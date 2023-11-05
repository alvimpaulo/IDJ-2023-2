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

public:
    EntityComponent(GameObject &associated, int currentHp,
                    int maxHp,

                    int maxMp,
                    int currentMp,

                    int strength,
                    int wisdom,
                    int dexterity,
                    int agility,

                    int aggro, bool isIndicated);
    void virtual Update(float dt) = 0;
    void virtual Render() = 0;
    bool virtual Is(std::string type) = 0;
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
    void physicalAttack(EntityComponent *target);
    void useSkill(EntityComponent *target);
    void defend();

    void loseHp(int amount);
    void gainHp(int amount);

    void loseMp(int amount);
    void gainMp(int amount);

    bool getIsIndicated();
    void setIsIndicated(bool newState);
};

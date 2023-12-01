#include "Entities/Entity.hpp"
#include "algorithm"

EntityComponent::EntityComponent(GameObject &associated, std::string type, int currentHp,
                                 int maxHp,

                                 int maxMp,
                                 int currentMp,

                                 int strength,
                                 int wisdom,
                                 int dexterity,
                                 int agility,

                                 int aggro, bool isSelected, Vec2 IdlePosition) : Component(associated, type), currentHp(currentHp),
                                                               maxHp(maxHp), maxMp(maxMp), currentMp(currentMp), strength(strength), wisdom(wisdom), dexterity(dexterity), agility(agility), isIndicated(isSelected)
{
    isOnAnimation = false;
    attackAnimationFrames = 100;
    currentAnimationFrame = 0;
    hasAttackFinished = true;
    isIdle = true;

    target = nullptr;

    this->IdlePosition = IdlePosition;
}
void EntityComponent::startPhysicalAttack(EntityComponent *target)
{
    isOnAnimation = true;
    hasAttackFinished = false;
    currentAnimationFrame = 1;
    isIdle = false;
    this->target = target;
}
void EntityComponent::useSkill(EntityComponent *target)
{
    target->loseHp(target->wisdom - this->wisdom);
}
void EntityComponent::defend()
{
    this->strength += 1;
}

void EntityComponent::loseHp(int amount)
{
    if (amount > 0)
    {
        this->currentHp -= amount;
        if (this->currentHp <= 0)
        {
            currentHp = 0;
        }
    }
}
void EntityComponent::gainHp(int amount)
{
    this->currentHp += amount;
    this->currentHp = std::min(currentHp, this->maxHp);
}

void EntityComponent::loseMp(int amount)
{
    this->currentMp -= amount;
    this->currentMp = std::max(currentMp, 0);
}
void EntityComponent::gainMp(int amount)
{
    this->currentMp += amount;
    this->currentMp = std::min(currentMp, this->maxMp);
}

int EntityComponent::getCurrentHp()
{
    return this->currentHp;
}
int EntityComponent::getMaxHp()
{
    return this->maxHp;
}
int EntityComponent::getCurrentMp()
{
    return this->currentMp;
}
int EntityComponent::getMaxMp()
{
    return this->maxMp;
}
int EntityComponent::getStrength()
{
    return this->strength;
}
int EntityComponent::getWisdom()
{
    return this->wisdom;
}
int EntityComponent::getDexterity()
{
    return this->dexterity;
}

int EntityComponent::getAggro()
{
    return this->aggro;
}

void EntityComponent::setIsIndicated(bool newState)
{
    this->isIndicated = newState;
}

bool EntityComponent::getIsIndicated()
{
    return isIndicated;
}

void EntityComponent::setTarget(EntityComponent *newTarget)
{

    if (target == nullptr)
    {
        target = newTarget;
    }
}
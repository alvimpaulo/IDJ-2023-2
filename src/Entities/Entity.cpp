#include "Entities/Entity.hpp"
#include "algorithm"
#include "Entity.hpp"

EntityComponent::EntityComponent(GameObject *associated, std::string type, int currentHp,
                                 int maxHp,

                                 int maxMp,
                                 int currentMp,

                                 int strength,
                                 int wisdom,
                                 int dexterity,
                                 int agility,

                                 int aggro, bool isSelected, Vec2 IdlePosition, Sprite *idleSprite, Sprite *runSprite, Sprite *attackSprite, Sprite *criticalSprite) : Component(associated, type), currentHp(currentHp),
                                                                                                                                                                       maxHp(maxHp), maxMp(maxMp), currentMp(currentMp), strength(strength), wisdom(wisdom), dexterity(dexterity), agility(agility), isIndicated(isSelected)
{
    hasAttackFinished = true;
    isIdle = true;

    this->IdlePosition = IdlePosition;


    this->animations = {new Animation(
        30, IdlePosition, IdlePosition, idleSprite, true, nullptr,
        AnimationPhase::Phase::Idle, associated)};
    this->animations.front()->startAnimation();
    this->associated->AddComponent(this->animations.front());
}
void EntityComponent::startPhysicalAttack(EntityComponent *target)
{
    hasAttackFinished = false;
    isIdle = false;
    this->animations.push_front(new Animation(
        120, IdlePosition, target->associated->getBox().GetCenter(), nullptr, false, [this]()
        { std::cout << "Physical attack " << this->getType() << " acabou" << std::endl; },
        AnimationPhase::Phase::Run, associated));
    this->animations.front()->startAnimation();
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

void EntityComponent::goToNextAnimation()
{
    if (animations.size() > 1)
    {
        auto aux = animations.front();
        animations.pop_front();
        animations.push_back(aux);
    }
}

void EntityComponent::Update(float dt)
{
    auto currentAnimation = (Animation *)associated->GetComponent("Animation");
    if (currentAnimation)
    {
        if (animations.front() != currentAnimation)
        {
            // new animation
            associated->RemoveComponent(currentAnimation);
            associated->AddComponent(animations.front());
        }
    }
}

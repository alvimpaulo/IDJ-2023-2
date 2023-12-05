#include "Entities/Entity.hpp"
#include "algorithm"
#include "Entity.hpp"
#include "BattleState.hpp"

EntityComponent::EntityComponent(GameObject *associated, std::string type, int currentHp,
                                 int maxHp,

                                 int maxMp,
                                 int currentMp,

                                 int strength,
                                 int wisdom,
                                 int dexterity,
                                 int agility,

                                 int aggro, bool isSelected, Vec2 IdlePosition, Sprite *idleSprite, Sprite *runSprite, Sprite *runBackSprite, Sprite *attackSprite, Sprite *criticalSprite) : Component(associated, type), currentHp(currentHp),
                                                                                                                                                                                              maxHp(maxHp), maxMp(maxMp), currentMp(currentMp), strength(strength), wisdom(wisdom), dexterity(dexterity), agility(agility), isIndicated(isSelected)
{
    isIdle = true;

    this->IdlePosition = IdlePosition;
    this->idleSprite = idleSprite;
    this->runSprite = runSprite;
    this->runBackSprite = runBackSprite;
    this->attackSprite = attackSprite;
    this->criticalSprite = criticalSprite;

    this->animations = {new Animation(
        30, IdlePosition, IdlePosition, idleSprite, true, nullptr, nullptr,
        AnimationPhase::Phase::Idle, associated)};
    this->associated->AddComponent(this->animations.front());
}

void physicalAttackEnd(EntityComponent *comp, EntityComponent *target)
{
    std::cout << "Physical attack " << comp->getType() << " acabou" << std::endl;
    target->loseHp(comp->getStrength());
    comp->animations.push_front(new Animation(
        60, target->associated->getScaledBox().GetCenter(), comp->IdlePosition, comp->runBackSprite, false, [comp]
        { std::cout << "Volta do ataque começou" << std::endl; },
        [comp]()
        {
            std::cout << "Volta do ataque acabou" << std::endl;
            comp->isIdle = true;
            comp->animations.pop_front();
            BattleState::GetInstance()->setRound(BattleState::Round::EnemyActionSelect);
        },
        AnimationPhase::Phase::RunBack, comp->associated));
}

void EntityComponent::physicalAttack(EntityComponent *target)
{
    isIdle = false;
    auto targetPosition = target->associated->getScaledBox().GetCenter();

    this->animations.push_front(new Animation(
        30, IdlePosition, targetPosition, this->runSprite, false,
        [this]()
        { std::cout << "Começou o physical attack da entity " << this->getType() << std::endl; },
        [this, target]()
        { this->animations.pop_front();
        physicalAttackEnd(this, target); },
        AnimationPhase::Phase::Run, associated));
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
            auto currentSprite = (Sprite *)associated->GetComponent("Sprite");
            if (currentSprite)
            {
                associated->RemoveComponent(currentSprite);
            }
            associated->AddComponent(animations.front());
            if (animations.front()->sprite)
            {
                associated->AddComponent(animations.front()->sprite);
            }
            animations.front()->StartAnimation();
        }
        else
        {
            auto currentSprite = (Sprite *)associated->GetComponent("Sprite");
            if (currentSprite == nullptr)
            {
                if (animations.front()->sprite)
                    associated->AddComponent(animations.front()->sprite);
            }
        }
    }
    else
    {
        if (animations.empty() == false)
        {
            associated->AddComponent(animations.front());
            auto currentSprite = (Sprite *)associated->GetComponent("Sprite");
            if (currentSprite == nullptr)
            {
                associated->AddComponent(animations.front()->sprite);
            }
            animations.front()->StartAnimation();
        }
    }
}

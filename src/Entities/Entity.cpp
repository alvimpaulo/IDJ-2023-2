#include "Entities/Entity.hpp"
#include "algorithm"
#include "Entity.hpp"
#include "BattleState.hpp"
#include "DamageText.hpp"
#include "HealText.hpp"
#include "MpLostText.hpp"
#include "MpGainText.hpp"

EntityComponent::EntityComponent(GameObject *associated, std::string type, int currentHp,
                                 int maxHp,

                                 int maxMp,
                                 int currentMp,

                                 int strength,
                                 int wisdom,
                                 int dexterity,
                                 int agility,

                                 int aggro, bool isSelected, Vec2 IdlePosition, Sprite *idleSprite) : Component(associated, type)
{
    isIdle = true;
    this->currentHp = maxHp;
    this->maxHp = maxHp;
    this->maxMp = maxMp;
    this->currentMp = maxMp;
    this->strength = strength;
    this->wisdom = wisdom;
    this->dexterity = dexterity;
    this->agility = agility;
    this->isIndicated = isSelected;
    this->IdlePosition = IdlePosition;
    this->rhythmAttackCount = 0;

    std::random_device os_seed;
    const uint_least32_t seed = os_seed();
    generator = std::mt19937(seed);

    this->setNewAnimation(new Animation(
        30, IdlePosition, IdlePosition, idleSprite, true, nullptr, nullptr,
        AnimationPhase::Phase::Idle, associated));
}

void EntityComponent::loseHp(int amount)
{
    amount = std::max(1, amount);
    auto damageTextObj = new GameObject();
    auto damageTextPtr = new DamageText(damageTextObj, amount, this->associated->getScaledBox().GetCenter(), this->associated->getScaledBox().GetCenter() + Vec2(0, 200), 2);
    damageTextObj->AddComponent(damageTextPtr);
    BattleState::GetInstance()->AddObject(damageTextObj);

    this->currentHp -= amount;
    if (this->currentHp <= 0)
    {
        currentHp = 0;
    }
}
void EntityComponent::gainHp(int amount)
{
    amount = std::max(1, amount);
    auto healTextObj = new GameObject();
    auto healTextPtr = new HealText(healTextObj, amount, this->associated->getScaledBox().GetCenter(), this->associated->getScaledBox().GetCenter() + Vec2(0, 200), 2);
    healTextObj->AddComponent(healTextPtr);
    BattleState::GetInstance()->AddObject(healTextObj);

    this->currentHp += amount;
    if (this->currentHp <= 0)
    {
        currentHp = 0;
    }
    this->currentHp = std::min(currentHp, this->maxHp);
}

void EntityComponent::loseMp(int amount)
{
    amount = std::max(1, amount);
    currentMp -= amount;
    auto loseMpTextObj = new GameObject();
    auto loseMpTextPtr = new MpLostText(loseMpTextObj, amount, this->associated->getScaledBox().GetCenter(), this->associated->getScaledBox().GetCenter() + Vec2(0, 200), 2);
    loseMpTextObj->AddComponent(loseMpTextPtr);
    BattleState::GetInstance()->AddObject(loseMpTextObj);
    this->currentMp = std::max(currentMp, 0);
}
void EntityComponent::gainMp(int amount)
{
    auto gainMpObj = new GameObject();
    auto gainMpPtr = new MpGainText(gainMpObj, amount, this->associated->getScaledBox().GetCenter(), this->associated->getScaledBox().GetCenter() + Vec2(0, 200), 2);
    gainMpObj->AddComponent(gainMpPtr);
    BattleState::GetInstance()->AddObject(gainMpObj);
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

void EntityComponent::Update(float dt)
{
    if (currentAnimation)
    {
        auto currentSprite = (Sprite *)associated->GetComponent("Sprite");
        if (currentSprite == nullptr)
        {
            if (currentAnimation->sprite)
                associated->AddComponent(currentAnimation->sprite);
        }
    }
}

void EntityComponent::setNewAnimation(Animation *newAnimation)
{
    if (currentAnimation)
    {
        auto animation = associated->GetComponent("Animation");
        auto currentSprite = (Sprite *)associated->GetComponent("Sprite");

        this->currentAnimation = newAnimation;
        currentAnimation->StartAnimation();
        associated->AddComponent(newAnimation);

        if (animation)
        {
            associated->RemoveComponent(animation);
        }

        if (currentSprite)
        {
            associated->RemoveComponent(currentSprite);
        }
    }
    else
    {
        this->currentAnimation = newAnimation;
        currentAnimation->StartAnimation();
        associated->AddComponent(newAnimation);
    }
}

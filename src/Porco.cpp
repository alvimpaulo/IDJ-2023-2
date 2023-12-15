#include "Porco.hpp"
#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Collider.hpp"
#include "Game.hpp"
#include "BattleState.hpp"
#include "EndState.hpp"

Porco::Porco(GameObject *associated, int currentHp,
             int maxHp,

             int maxMp,
             int currentMp,

             int strength,
             int wisdom,
             int dexterity,
             int agility,

             int aggro, Sprite *idleSprite) : EntityComponent(associated, "Porco",
                                                              currentHp, maxHp, maxMp, currentMp, strength, wisdom, dexterity, agility,
                                                              aggro, false, Vec2(SCREEN_WIDTH - associated->getScaledBox().w, SCREEN_HEIGHT - associated->getScaledBox().h), idleSprite)
{
    setIsVisible(true);

    // auto collider = new Collider(associated);
    // this->associated->AddComponent(collider);
}

Porco::~Porco()
{
}

void Porco::Start()
{
}

void Porco::Update(float dt)
{
    EntityComponent::Update(dt);

    if (isIdle)
    {

        associated->setBoxCenter(Vec2(IdlePosition.x, IdlePosition.y));
    }

    if(this->getCurrentHp() == 0){
        BattleState::GetInstance()->requestPop();
        Game::GetInstance().Push(EndState::GetInstance(true));
    }
}

void Porco::Render()
{
}

void Porco::NotifyCollision(GameObject &other)
{
}

void Porco::physicalAttackStart(EntityComponent *target)
{
}

void Porco::physicalAttackEnd(EntityComponent *target)
{
    this->setNewAnimation(new Animation(
        15, target->associated->getScaledBox().GetCenter(), target->associated->getScaledBox().GetCenter(), Porco::CreateAttackSprite(associated), false, [this] {},
        [this, target]()
        {
            std::uniform_int_distribution<uint_least32_t> distributeDamage(1 + getStrength(), getStrength() * 4);
            auto damage = distributeDamage(generator);
            // auto damage = 300;

            target->loseHp(damage - target->getStrength() / 2);

            // auto targetPosition = target->associated->getScaledBox().GetCenter() + Vec2(target->associated->getScaledBox().w / 2 + this->associated->getScaledBox().w / 2, 0);
            auto targetPosition = target->associated->getScaledBox().GetCenter();

            this->setNewAnimation(new Animation(
                30, targetPosition, IdlePosition, Porco::CreateRunBackSprite(associated), false,
                []() {},
                [this, target]()
                {
                    auto newIdleSprite = Porco::CreateIdleSprite(associated);
                    this->isIdle = true;
                    BattleState::GetInstance()->setRound(BattleState::Round::PlayerCharacterSelectInit);
                    this->setNewAnimation(new Animation(
                        30, IdlePosition, IdlePosition, newIdleSprite, true, nullptr, nullptr,
                        AnimationPhase::Phase::Idle, associated));
                },
                AnimationPhase::Phase::RunBack, associated));
        },
        AnimationPhase::Phase::LoadAttack, this->associated));
}

void Porco::physicalAttack(EntityComponent *target)
{
    isIdle = false;
    auto targetPosition = target->associated->getScaledBox().GetCenter() + Vec2(target->associated->getScaledBox().w / 2 + this->associated->getScaledBox().w / 2, 0);

    this->setNewAnimation(new Animation(
        60, IdlePosition, targetPosition, Porco::CreateRunSprite(associated), false,
        [this, target]()
        { this->physicalAttackStart(target); },
        [this, target]()
        { physicalAttackEnd(target); },
        AnimationPhase::Phase::Run, associated));
}

void Porco::rhythmAttackStart(EntityComponent *target)
{
}

void Porco::rhythmAttackEnd(EntityComponent *target)
{
}

void Porco::rhythmAttack(EntityComponent *target)
{
}

void Porco::useSkill(EntityComponent *target)
{
    std::uniform_int_distribution<uint_least32_t> distrib(1, 20);
    this->gainHp(distrib(generator));
    this->loseMp(5);
}
void Porco::defend()
{
    std::uniform_int_distribution<uint_least32_t> distrib(1, 20);
    this->gainHp(distrib(generator));
    this->loseMp(5);
}

Sprite *Porco::CreateIdleSprite(GameObject *associated)
{
    return new Sprite(associated, "assets/img/Javtalista/NewIdle.png", 16, 0.1, 0, 255, false, false);
}

Sprite *Porco::CreateRunSprite(GameObject *associated)
{
    return new Sprite(associated, "assets/img/Javtalista/NewRun.png", 7, 0.1, 0, 255, false, false);
}

Sprite *Porco::CreateRunBackSprite(GameObject *associated)
{
    return new Sprite(associated, "assets/img/Javtalista/NewRunBack.png", 7, 0.1, 0, 255, false, false);
}

Sprite *Porco::CreateAttackSprite(GameObject *associated)
{
    return new Sprite(associated, "assets/img/Javtalista/NewAttack.png", 4, 10);
}

Sprite *Porco::CreateAttackBackSprite(GameObject *associated)
{
    return new Sprite(associated, "assets/img/Javtalista/NewAttack.png", 4, 10);
}
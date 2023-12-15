#include "Warrior.hpp"
#include "Sprite.hpp"
#include "Collider.hpp"
#include "Game.hpp"
#include "InputManager.hpp"
#include "BattleState.hpp"
#include "random"

Warrior::Warrior(GameObject *associated, int currentHp,
                 int maxHp,

                 int maxMp,
                 int currentMp,

                 int strength,
                 int wisdom,
                 int dexterity,
                 int agility,

                 int aggro, Sprite *idleSprite) : EntityComponent(associated, "Warrior", currentHp, maxHp,
                                                                  maxMp, currentMp, strength, wisdom, dexterity, agility, aggro,
                                                                  false,
                                                                  Vec2(0 + associated->getScaledBox().x / 2 + 100, SCREEN_HEIGHT - associated->getScaledBox().h - (SCREEN_HEIGHT / 10)),
                                                                  idleSprite)
{
    speed = {0.0f, 0.0f};

    linearSpeed = 0.0f;

    // auto collider = new Collider(associated);
    // this->associated->AddComponent(collider);
}

Warrior::~Warrior()
{
}

void Warrior::Start()
{
    auto bodyPtr = Game::GetInstance().GetCurrentState()->GetObjectPtr(associated);
}
void Warrior::Update(float dt)
{
    EntityComponent::Update(dt);

    if (isIdle)
    {

        associated->setBoxCenter(Vec2(IdlePosition.x, IdlePosition.y));
    }
    else
    {
    }
    // if (currentHp <= 0)
    // {
    //     this->associated->RequestDelete();
    // }
}
void Warrior::Render()
{
}
void Warrior::NotifyCollision(GameObject &other)
{

    // if (currentHp <= 0)
    // {
    //     associated->RequestDelete();
    // }
}

void Warrior::physicalAttackStart(EntityComponent *target)
{
}

void Warrior::physicalAttackEnd(EntityComponent *target)
{
    rhythmAttackStart(target);
}

void Warrior::physicalAttack(EntityComponent *target)
{
    isIdle = false;
    auto targetPosition = target->associated->getScaledBox().GetCenter() - Vec2(target->associated->getScaledBox().w / 2 + this->associated->getScaledBox().w / 2, 0);

    this->setNewAnimation(new Animation(
        30, IdlePosition, targetPosition, Warrior::CreateRunSprite(associated), false,
        [this, target]()
        { physicalAttackStart(target); },
        [this, target]()
        { physicalAttackEnd(target); },
        AnimationPhase::Phase::Run, associated));
}

void Warrior::rhythmAttackStart(EntityComponent *target)
{

    auto targetPosition = target->associated->getScaledBox().GetCenter() - Vec2(target->associated->getScaledBox().w / 2 + this->associated->getScaledBox().w / 2, 0);
    BattleState::GetInstance()->setRound(BattleState::Round::PlayerRhythm);

    // Mostrar as bolas na tela e ver quantas a pessoa conseguiu clicar.
    //  target->loseHp(this->getStrength() * numeroDebolasMostradoNaTela + 1);
}

void Warrior::rhythmAttackEnd(EntityComponent *target)
{
    rhythmAttackCount = 0;
    this->setNewAnimation(new Animation(
        30, target->associated->getScaledBox().GetCenter(), this->IdlePosition, Warrior::CreateRunBackSprite(associated), false, [] {},
        [this]()
        {
            auto newIdleSprite = Warrior::CreateIdleSprite(associated);
            this->isIdle = true;
            BattleState::GetInstance()->setRound(BattleState::Round::EnemyActionSelect);
            this->setNewAnimation(new Animation(
                30, IdlePosition, IdlePosition, newIdleSprite, true, nullptr, nullptr,
                AnimationPhase::Phase::Idle, associated));
        },
        AnimationPhase::Phase::RunBack, this->associated));
}

void Warrior::rhythmAttack(EntityComponent *target)
{
    std::uniform_int_distribution<uint_least32_t> distribute(this->getStrength(), this->getStrength() * 2);
    const auto damage = distribute(generator) - (target->getStrength() / 2);
    if (rhythmAttackCount % 2 == 0)
    {
        // forward animation
        this->setNewAnimation(new Animation(
            30, associated->getScaledBox().GetCenter(), associated->getScaledBox().GetCenter(), Warrior::CreateAttackSprite(associated), false,
            [this, target, damage]()
            {
                target->loseHp(damage);
            },
            [this, target]() {

            },
            AnimationPhase::Phase::Run, associated));
    }
    else
    {
        // backwards animation
        this->setNewAnimation(new Animation(
            30, associated->getScaledBox().GetCenter(), associated->getScaledBox().GetCenter(), Warrior::CreateAttackBackSprite(associated), false,
            [this, target, damage]()
            {
                target->loseHp(damage);
            },
            [this, target]() {

            },
            AnimationPhase::Phase::Run, associated));
    }

    rhythmAttackCount++;
}
void Warrior::useSkill(EntityComponent *target)
{
    isIdle = false;
    std::uniform_int_distribution<uint_least32_t> distrib(1, 20);
    this->gainHp(distrib(generator));
    this->loseMp(5);
    BattleState::GetInstance()->setRound(BattleState::Round::EnemyActionSelect);
    isIdle = true;
}
void Warrior::defend()
{
    isIdle = false;
    std::uniform_int_distribution<uint_least32_t> distrib(5, 10);
    this->gainMp(distrib(generator));
    BattleState::GetInstance()->setRound(BattleState::Round::EnemyActionSelect);
    isIdle = true;
}

Sprite *Warrior::CreateIdleSprite(GameObject *associated)
{
    return new Sprite(associated, "assets/img/Warrior/NewIdle.png", 10, 10);
}

Sprite *Warrior::CreateRunSprite(GameObject *associated)
{
    return new Sprite(associated, "assets/img/Warrior/newRun.png", 6, 10);
}

Sprite *Warrior::CreateRunBackSprite(GameObject *associated)
{
    return new Sprite(associated, "assets/img/Warrior/RunBack.png", 6, 10);
}

Sprite *Warrior::CreateAttackSprite(GameObject *associated)
{
    return new Sprite(associated, "assets/img/Warrior/NewAttack1.png", 4, 10);
}

Sprite *Warrior::CreateAttackBackSprite(GameObject *associated)
{
    return new Sprite(associated, "assets/img/Warrior/NewAttack1Volta.png", 4, 10);
}
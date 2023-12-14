#include "Bargudin.hpp"
#include "Sprite.hpp"
#include "Collider.hpp"
#include "Game.hpp"
#include "InputManager.hpp"
#include "BattleState.hpp"
#include "random"

Bargudin::Bargudin(GameObject *associated, int currentHp,
                 int maxHp,

                 int maxMp,
                 int currentMp,

                 int strength,
                 int wisdom,
                 int dexterity,
                 int agility,

                 int aggro, Sprite *idleSprite) : EntityComponent(associated, "Bargudin", currentHp, maxHp,
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

Bargudin::~Bargudin()
{
}

void Bargudin::Start()
{
    auto bodyPtr = Game::GetInstance().GetCurrentState()->GetObjectPtr(associated);
}
void Bargudin::Update(float dt)
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
void Bargudin::Render()
{
}
void Bargudin::NotifyCollision(GameObject &other)
{

    // if (currentHp <= 0)
    // {
    //     associated->RequestDelete();
    // }
}

void Bargudin::physicalAttackStart(EntityComponent *target)
{
}

void Bargudin::physicalAttackEnd(EntityComponent *target)
{
    rhythmAttackStart(target);
}

void Bargudin::physicalAttack(EntityComponent *target)
{
    isIdle = false;
    auto targetPosition = target->associated->getScaledBox().GetCenter() - Vec2(target->associated->getScaledBox().w / 2 + this->associated->getScaledBox().w / 2, 0);

    this->setNewAnimation(new Animation(
        30, IdlePosition, targetPosition, Bargudin::CreateRunSprite(associated), false,
        [this, target]()
        { physicalAttackStart(target); },
        [this, target]()
        { physicalAttackEnd(target); },
        AnimationPhase::Phase::Run, associated));
}

void Bargudin::rhythmAttackStart(EntityComponent *target)
{

    auto targetPosition = target->associated->getScaledBox().GetCenter() - Vec2(target->associated->getScaledBox().w / 2 + this->associated->getScaledBox().w / 2, 0);
    BattleState::GetInstance()->setRound(BattleState::Round::PlayerRhythm);

    // Mostrar as bolas na tela e ver quantas a pessoa conseguiu clicar.
    //  target->loseHp(this->getStrength() * numeroDebolasMostradoNaTela + 1);
}

void Bargudin::rhythmAttackEnd(EntityComponent *target)
{
    rhythmAttackCount = 0;
    this->setNewAnimation(new Animation(
        60, target->associated->getScaledBox().GetCenter(), this->IdlePosition, Bargudin::CreateRunBackSprite(associated), false, [] {},
        [this]()
        {
            auto newIdleSprite = Bargudin::CreateIdleSprite(associated);
            this->isIdle = true;
            BattleState::GetInstance()->setRound(BattleState::Round::EnemyActionSelect);
            this->setNewAnimation(new Animation(
                30, IdlePosition, IdlePosition, newIdleSprite, true, nullptr, nullptr,
                AnimationPhase::Phase::Idle, associated));
        },
        AnimationPhase::Phase::RunBack, this->associated));
}

void Bargudin::rhythmAttack(EntityComponent *target)
{
    if (rhythmAttackCount % 2 == 0)
    {
        //forward animation
        this->setNewAnimation(new Animation(
            30, associated->getScaledBox().GetCenter(), associated->getScaledBox().GetCenter(), Bargudin::CreateAttackSprite(associated), false,
            [this, target]() {},
            [this, target]()
            {
                target->loseHp(std::max(1, this->getStrength() - target->getStrength()));
            },
            AnimationPhase::Phase::Run, associated));
    }
    else
    {
        //backwards animation
        this->setNewAnimation(new Animation(
            30, associated->getScaledBox().GetCenter(), associated->getScaledBox().GetCenter(), Bargudin::CreateAttackBackSprite(associated), false,
            [this, target]() {},
            [this, target]()
            {
                target->loseHp(std::max(1, this->getStrength() - target->getStrength()));
            },
            AnimationPhase::Phase::Run, associated));
    }

    rhythmAttackCount++;
}
void Bargudin::useSkill(EntityComponent *target)
{
    isIdle = false;
    target->loseHp(this->wisdom - target->getWisdom());
}
void Bargudin::defend()
{
    this->strength += 1;
}

Sprite *Bargudin::CreateIdleSprite(GameObject *associated)
{
    return new Sprite(associated, "assets/img/Bargudin/NewIdle.png", 10, 10);
}

Sprite *Bargudin::CreateRunSprite(GameObject *associated)
{
    return new Sprite(associated, "assets/img/Bargudin/newRun.png", 6, 10);
}

Sprite *Bargudin::CreateRunBackSprite(GameObject *associated)
{
    return new Sprite(associated, "assets/img/Bargudin/RunBack.png", 6, 10);
}

Sprite *Bargudin::CreateAttackSprite(GameObject *associated)
{
    return new Sprite(associated, "assets/img/Bargudin/NewAttack1.png", 4, 10);
}

Sprite *Bargudin::CreateAttackBackSprite(GameObject *associated)
{
    return new Sprite(associated, "assets/img/Bargudin/NewAttack1Volta.png", 4, 10);
}
#include "Bargudin.hpp"
#include "Sprite.hpp"
#include "Collider.hpp"
#include "Game.hpp"
#include "InputManager.hpp"
#include "BattleState.hpp"
#include "random"
#include "EndState.hpp"

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
                                                                  Vec2(0 + associated->getScaledBox().x / 2 + 100, SCREEN_HEIGHT - associated->getScaledBox().h ),
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

    if(this->getCurrentHp() == 0){
        BattleState::GetInstance()->requestPop();
        Game::GetInstance().Push(EndState::GetInstance(false));
    }

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
        30, target->associated->getScaledBox().GetCenter(), this->IdlePosition, Bargudin::CreateRunBackSprite(associated), false, [] {},
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
    std::uniform_int_distribution<uint_least32_t> distribute(this->getStrength(), this->getStrength() * 2);
    const auto damage = distribute(generator);
    if (rhythmAttackCount % 2 == 0)
    {
        // forward animation
        this->setNewAnimation(new Animation(
            30, associated->getScaledBox().GetCenter(), associated->getScaledBox().GetCenter(), Bargudin::CreateAttackSprite(associated), false,
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
            30, associated->getScaledBox().GetCenter(), associated->getScaledBox().GetCenter(), Bargudin::CreateAttackBackSprite(associated), false,
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
void Bargudin::useSkill(EntityComponent *target)
{
    isIdle = false;
    std::uniform_int_distribution<uint_least32_t> distrib(1, 20);
    this->gainHp(distrib(generator));
    this->loseMp(5);
    BattleState::GetInstance()->setRound(BattleState::Round::PlayerCharacterSelectInit);
    isIdle = true;
}
void Bargudin::defend()
{
    isIdle = false;
    std::uniform_int_distribution<uint_least32_t> distrib(5, 10);
    this->gainMp(distrib(generator));
    BattleState::GetInstance()->setRound(BattleState::Round::EnemyActionSelect);
    isIdle = true;
}

Sprite *Bargudin::CreateIdleSprite(GameObject *associated)
{
    return new Sprite(associated, "assets/img/Bargudin/NewIdle.png", 8, 10);
}

Sprite *Bargudin::CreateRunSprite(GameObject *associated)
{
    return new Sprite(associated, "assets/img/Bargudin/NewRun.png", 4, 10);
}

Sprite *Bargudin::CreateRunBackSprite(GameObject *associated)
{
    return new Sprite(associated, "assets/img/Bargudin/NewRunBack.png", 4, 10);
}

Sprite *Bargudin::CreateAttackSprite(GameObject *associated)
{
    return new Sprite(associated, "assets/img/Bargudin/NewAttack.png", 3, 10);
}

Sprite *Bargudin::CreateAttackBackSprite(GameObject *associated)
{
    return new Sprite(associated, "assets/img/Bargudin/NewAttack.png", 3, 10);
}
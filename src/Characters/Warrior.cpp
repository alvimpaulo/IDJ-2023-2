#include "Warrior.hpp"
#include "Sprite.hpp"
#include "Collider.hpp"
#include "Game.hpp"
#include "InputManager.hpp"
#include "BattleState.hpp"

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
    std::cout << "Physical attack " << this->getType() << " acabou" << std::endl;
    target->loseHp(this->getStrength());
    this->setNewAnimation(new Animation(
        60, target->associated->getScaledBox().GetCenter(), this->IdlePosition, Warrior::CreateRunBackSprite(associated), false, [this] {},
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

void Warrior::physicalAttack(EntityComponent *target)
{
    isIdle = false;
    auto targetPosition = target->associated->getScaledBox().GetCenter();

    this->setNewAnimation(new Animation(
        30, IdlePosition, targetPosition, Warrior::CreateRunSprite(associated), false,
        [this, target]()
        { physicalAttackStart(target); },
        [this, target]()
        { physicalAttackEnd(target); },
        AnimationPhase::Phase::Run, associated));
}
void Warrior::useSkill(EntityComponent *target)
{
    target->loseHp(this->wisdom - target->getWisdom());
}
void Warrior::defend()
{
    this->strength += 1;
}

Sprite* Warrior::CreateIdleSprite(GameObject* associated){
    return new Sprite(associated, "assets/img/Warrior/NewIdle.png", 10, 10);
}

Sprite* Warrior::CreateRunSprite(GameObject* associated){
    return new Sprite(associated, "assets/img/Warrior/newRun.png", 6, 10);
}

Sprite* Warrior::CreateRunBackSprite(GameObject* associated){
    return new Sprite(associated, "assets/img/Warrior/RunBack.png", 6, 10);
}
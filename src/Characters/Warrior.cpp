#include "Warrior.hpp"
#include "Sprite.hpp"
#include "Collider.hpp"
#include "Game.hpp"
#include "InputManager.hpp"
#include "BattleState.hpp"

Warrior::Warrior(GameObject &associated, int currentHp,
                 int maxHp,

                 int maxMp,
                 int currentMp,

                 int strength,
                 int wisdom,
                 int dexterity,
                 int agility,

                 int aggro) : EntityComponent(associated, "Warrior", currentHp, maxHp,
                                              maxMp, currentMp, strength, wisdom, dexterity, agility, aggro,
                                              false, Vec2(0 + 50, SCREEN_HEIGHT - associated.getScaledBox().h - (SCREEN_HEIGHT / 10)))
{
    speed = {0.0f, 0.0f};

    linearSpeed = 0.0f;

    associated.setScale(Vec2(3, 3));

    auto ptrSprite = new Sprite(associated, "assets/img/Warrior/NewIdle.png", 10, 0.1);

    associated.AddComponent(ptrSprite);

    // auto collider = new Collider(associated);
    // this->associated.AddComponent(collider);
}

Warrior::~Warrior()
{
}

void Warrior::Start()
{
    auto bodyPtr = Game::GetInstance().GetCurrentState()->GetObjectPtr(&associated);
}
void Warrior::Update(float dt)
{
    if (isIdle)
    {

        associated.setBoxX(IdlePosition.x);
        associated.setBoxY(IdlePosition.y);
    }
    else
    {
        auto currentTargetDistance = Vec2::GetDistancePix(associated.getBox().GetCenter(), target->associated.getBox().GetCenter());
        auto currrentIdleDistance = Vec2::GetDistancePix(associated.getBox().GetCenter(), IdlePosition);

        if (currentTargetDistance <= 50 && currentAnimationFrame <= attackAnimationFrames / 2)
        {
            currentAnimationFrame = attackAnimationFrames / 2 + 1;
            target->loseHp(std::max(this->strength, 0));
        }
        else if (currrentIdleDistance <= 50 && currentAnimationFrame > attackAnimationFrames / 2)
        {
            isOnAnimation = false;
            hasAttackFinished = true;
            isIdle = true;
            target = nullptr;
            currentAnimationFrame = 0;
            BattleState::GetInstance()->setRound(BattleState::Round::EnemyActionSelect);
        }
        else if (currentAnimationFrame < attackAnimationFrames / 2)
        {
            currentAnimationFrame++;

            auto idleTargetDistanceX = Vec2::GetDistancePix(
                Vec2(IdlePosition.x, 0),
                Vec2(target->associated.getBox().GetCenter().x, 0));

            auto animationMoveDistance = idleTargetDistanceX / attackAnimationFrames * 2;

            associated.setBoxX(associated.getBox().x + animationMoveDistance);
        }
        else if (currentAnimationFrame > attackAnimationFrames / 2)
        {
            currentAnimationFrame++;

            auto idleTargetDistanceX = Vec2::GetDistancePix(
                Vec2(IdlePosition.x, 0),
                Vec2(target->associated.getBox().GetCenter().x, 0));

            auto animationMoveDistance = idleTargetDistanceX / attackAnimationFrames * 2;

            associated.setBoxX(associated.getBox().x - animationMoveDistance);
        }
    }
    // if (currentHp <= 0)
    // {
    //     this->associated.RequestDelete();
    // }
}
void Warrior::Render()
{
}
void Warrior::NotifyCollision(GameObject &other)
{

    // if (currentHp <= 0)
    // {
    //     associated.RequestDelete();
    // }
}
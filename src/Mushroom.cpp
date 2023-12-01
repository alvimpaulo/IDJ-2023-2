#include "Mushroom.hpp"
#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Collider.hpp"
#include "Game.hpp"
#include "BattleState.hpp"

Mushroom::Mushroom(GameObject &associated, int currentHp,
                   int maxHp,

                   int maxMp,
                   int currentMp,

                   int strength,
                   int wisdom,
                   int dexterity,
                   int agility,

                   int aggro) : EntityComponent(associated, "Mushroom", currentHp, maxHp, maxMp, currentMp, strength, wisdom, dexterity, agility, aggro, false, Vec2(SCREEN_WIDTH - associated.getScaledBox().w - 50, SCREEN_HEIGHT - associated.getScaledBox().h - (SCREEN_HEIGHT / 10)))
{
    setIsVisible(true);

    this->associated.setScale(Vec2(5, 5));

    auto mushroomSprite = new Sprite(associated, "assets/img/Monsters/Mushroom/NewIdle.png", 4, 0.1, 0, 255, true, false);
    this->associated.AddComponent(mushroomSprite);

    // auto collider = new Collider(associated);
    // this->associated.AddComponent(collider);
}

Mushroom::~Mushroom()
{
}

void Mushroom::Start()
{
}

void Mushroom::Update(float dt)
{

    if (isIdle)
    {

        associated.setBoxX(IdlePosition.x);
        associated.setBoxY(IdlePosition.y);
    }
    else
    {
        auto currentTargetDistance = Vec2::GetDistancePix(associated.getBox().GetCenter(), target->associated.getBox().GetCenter());
        auto currrentIdleDistance =  Vec2::GetDistancePix(associated.getBox().GetCenter(), IdlePosition);

        if (abs(currentTargetDistance) <= 50 && currentAnimationFrame <= attackAnimationFrames / 2)
        {
            currentAnimationFrame = attackAnimationFrames / 2 + 1;
            target->loseHp(std::max(this->strength, 0));
        }
        else if (abs(currrentIdleDistance) <= 50 && currentAnimationFrame > attackAnimationFrames / 2)
        {
            isOnAnimation = false;
            hasAttackFinished = true;
            isIdle = true;
            target = nullptr;
            currentAnimationFrame = 0;
            BattleState::GetInstance()->setRound(BattleState::Round::PlayerCharacterSelect);
        }
        else if (currentAnimationFrame < attackAnimationFrames / 2)
        {
            currentAnimationFrame++;

            auto idleTargetDistanceX = Vec2::GetDistancePix(
                Vec2(IdlePosition.x, 0),
                Vec2(target->associated.getBox().GetCenter().x, 0));

            auto animationMoveDistance = idleTargetDistanceX / attackAnimationFrames * 2;

            associated.setBoxX(associated.getBox().x - animationMoveDistance);
        }
        else if (currentAnimationFrame > attackAnimationFrames / 2)
        {
            currentAnimationFrame++;

            auto idleTargetDistanceX = Vec2::GetDistancePix(
                Vec2(IdlePosition.x, 0),
                Vec2(target->associated.getBox().GetCenter().x, 0));

            auto animationMoveDistance = idleTargetDistanceX / attackAnimationFrames * 2;

            associated.setBoxX(associated.getBox().x + animationMoveDistance);
        }
    }
}

void Mushroom::Render()
{
}

void Mushroom::NotifyCollision(GameObject &other)
{
}
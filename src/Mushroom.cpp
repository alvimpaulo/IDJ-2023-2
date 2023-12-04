#include "Mushroom.hpp"
#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Collider.hpp"
#include "Game.hpp"
#include "BattleState.hpp"

Mushroom::Mushroom(GameObject *associated, int currentHp,
                   int maxHp,

                   int maxMp,
                   int currentMp,

                   int strength,
                   int wisdom,
                   int dexterity,
                   int agility,

                   int aggro, Sprite *idleSprite) : EntityComponent(associated, "Mushroom",
                                                                    currentHp, maxHp, maxMp, currentMp, strength, wisdom, dexterity, agility,
                                                                    aggro, false, Vec2(SCREEN_WIDTH - associated->getScaledBox().w - 50, SCREEN_HEIGHT - associated->getScaledBox().h - (SCREEN_HEIGHT / 10)), idleSprite, nullptr, nullptr, nullptr)
{
    setIsVisible(true);

    // auto collider = new Collider(associated);
    // this->associated->AddComponent(collider);
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

        associated->setBoxX(IdlePosition.x);
        associated->setBoxY(IdlePosition.y);
    }
}

void Mushroom::Render()
{
}

void Mushroom::NotifyCollision(GameObject &other)
{
}
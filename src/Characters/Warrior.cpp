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

                 int aggro, Sprite *idleSprite, Sprite *runSprite, Sprite *runBackSprite) : EntityComponent(associated, "Warrior", currentHp, maxHp,
                                                                                                            maxMp, currentMp, strength, wisdom, dexterity, agility, aggro,
                                                                                                            false,
                                                                                                            Vec2(0 + associated->getScaledBox().x / 2 + 100, SCREEN_HEIGHT - associated->getScaledBox().h - (SCREEN_HEIGHT / 10)),
                                                                                                            idleSprite, runSprite, runBackSprite, nullptr, nullptr)
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
#include "Ranger.hpp"
#include "Sprite.hpp"
#include "Collider.hpp"
#include "Game.hpp"
#include "InputManager.hpp"

Ranger::Ranger(GameObject &associated, int currentHp,
               int maxHp,

               int maxMp,
               int currentMp,

               int strength,
               int wisdom,
               int dexterity,
               int agility,

               int aggro) : EntityComponent(associated, "Ranger", currentHp, maxHp, maxMp, currentMp, strength, wisdom, dexterity, agility, aggro, false)
{
    speed = {0.0f, 0.0f};

    linearSpeed = 0.0f;

    associated.setScale(Vec2(3, 3));

    auto ptrSprite = new Sprite(associated, "assets/img/Ranger/NewIdle.png", 10, 0.1);

    associated.AddComponent(ptrSprite);

    // auto collider = new Collider(associated);
    // this->associated.AddComponent(collider);
}

Ranger::~Ranger()
{
}

void Ranger::Start()
{
    auto bodyPtr = Game::GetInstance().GetCurrentState()->GetObjectPtr(&associated);
}
void Ranger::Update(float dt)
{

    associated.setBoxX(0 + 50);
    associated.setBoxY(SCREEN_HEIGHT - (associated.getScaledBox().h * 2) - (SCREEN_HEIGHT / 10));

    // if (currentHp <= 0)
    // {
    //     this->associated.RequestDelete();
    // }
}
void Ranger::Render()
{
}
void Ranger::NotifyCollision(GameObject &other)
{

    // if (currentHp <= 0)
    // {
    //     associated.RequestDelete();
    // }
}
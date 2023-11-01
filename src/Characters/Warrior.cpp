#include "Warrior.hpp"
#include "Sprite.hpp"
#include "Collider.hpp"
#include "Game.hpp"
#include "InputManager.hpp"

Warrior *Warrior::player = nullptr;

Warrior::Warrior(GameObject &associated) : Component(associated)
{
    speed = {0.0f, 0.0f};

    linearSpeed = 0.0f;
    hp = 20;
    auto ptrSprite = new Sprite(associated, "assets/img/Warrior/NewIdle.png", 10, 0.1);
    ptrSprite->SetScale(Vec2(3,3));

    associated.AddComponent(ptrSprite);

    auto collider = new Collider(associated, {3,3});
    this->associated.AddComponent(collider);

    player = this;
}

Warrior::~Warrior()
{
    player = nullptr;
}

void Warrior::Start()
{
    auto bodyPtr = Game::GetInstance().GetCurrentState()->GetObjectPtr(&associated);
}
void Warrior::Update(float dt)
{

    associated.setBoxCenter(Vec2(100, 100));

    if (hp <= 0)
    {
        this->associated.RequestDelete();
    }
}
void Warrior::Render()
{
}
bool Warrior::Is(std::string type)
{
    return type == "Warrior";
}

void Warrior::NotifyCollision(GameObject &other)
{

    if (hp <= 0)
    {
        associated.RequestDelete();
    }
}
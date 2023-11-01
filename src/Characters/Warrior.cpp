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
    currentHp = 20;

    associated.setScale(Vec2(3, 3));

    auto ptrSprite = new Sprite(associated, "assets/img/Warrior/NewIdle.png", 10, 0.1);

    associated.AddComponent(ptrSprite);

    auto collider = new Collider(associated);
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

    associated.setBoxX(0 + 50);
    associated.setBoxY(SCREEN_HEIGHT - associated.getScaledBox().h - (SCREEN_HEIGHT/10));

    if (currentHp <= 0)
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

    if (currentHp <= 0)
    {
        associated.RequestDelete();
    }
}
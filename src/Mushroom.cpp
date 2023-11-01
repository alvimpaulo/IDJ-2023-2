#include "Mushroom.hpp"
#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Collider.hpp"
#include "Game.hpp"

Mushroom::Mushroom(GameObject &associated) : Component(associated)
{
    this->hp = 100;

    auto mushroomSprite = new Sprite(associated, "assets/img/Monsters/Mushroom/NewIdle.png", 4, 0.1, 0, 255, true, false);
    mushroomSprite->SetScale(Vec2(5, 5));
    this->associated.AddComponent(mushroomSprite);

    auto collider = new Collider(associated);
    collider->SetScale(Vec2(5, 5));
    this->associated.AddComponent(collider);
}

Mushroom::~Mushroom()
{
}

void Mushroom::Start()
{
}

void Mushroom::Update(float dt)
{
}

void Mushroom::Render()
{
}

bool Mushroom::Is(std::string type)
{
    return type == "Mushroom";
}

void Mushroom::NotifyCollision(GameObject &other)
{
}
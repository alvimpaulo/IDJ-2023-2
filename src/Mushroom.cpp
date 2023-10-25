#include "Mushroom.hpp"
#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Collider.hpp"

Mushroom::Mushroom(GameObject &associated) : Component(associated)
{
    this->hp = 100;

    auto alienSprite = new Sprite(associated, "assets/img/Monsters/Mushroom/Idle.png", 4, 10);
    this->associated.AddComponent(alienSprite);

    auto collider = new Collider(associated);
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
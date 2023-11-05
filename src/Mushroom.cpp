#include "Mushroom.hpp"
#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Collider.hpp"
#include "Game.hpp"

Mushroom::Mushroom(GameObject &associated, int currentHp,
                   int maxHp,

                   int maxMp,
                   int currentMp,

                   int strength,
                   int wisdom,
                   int dexterity,
                   int agility,

                   int aggro) : EntityComponent(associated, currentHp, maxHp, maxMp, currentMp, strength, wisdom, dexterity, agility, aggro, false)
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

    if (getIsVisible())
    {
        associated.setBoxX(SCREEN_WIDTH - associated.getScaledBox().w - 50);
        associated.setBoxY(SCREEN_HEIGHT - associated.getScaledBox().h - (SCREEN_HEIGHT / 10));
    }
    else
    {
        associated.setBoxCenter(Vec2(-SCREEN_WIDTH, -SCREEN_HEIGHT));
    }
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
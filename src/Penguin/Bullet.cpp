#include "Penguin/Bullet.hpp"
#include "Sprite.hpp"
#include "Collider.hpp"
#include "Penguin/PenguinBody.hpp"
#include "Penguin/PenguinCannon.hpp"
#include "Penguin/Alien.hpp"
#include "Penguin/Minion.hpp"

Bullet::Bullet(GameObject &associated,
               float angleRad,
               float speed,
               int damage,
               float maxDistance,
               std::string sprite,
               int frameCount, float frameTime, bool targetsPlayer) : Component(associated, type)
{
    this->damage = damage;
    this->distanceLeft = maxDistance;
    this->targetsPlayer = targetsPlayer;

    this->speed = Vec2(speed * cos(angleRad), speed * sin(angleRad));

    auto spritePtr = new Sprite(associated, sprite, frameCount, frameTime);
    associated.SetAngle(Vec2::rad2deg(angleRad));
    associated.AddComponent(spritePtr);

    auto collider = new Collider(associated);
    this->associated.AddComponent(collider);
}
void Bullet::Update(float dt)
{
    auto srcPos = this->associated.getBox().GetCenter();

    Vec2 dstPos = srcPos + (this->speed * dt);

    auto distance = Vec2::GetDistancePix(srcPos, dstPos);

    this->associated.setBoxCenter(dstPos);
    distanceLeft -= distance;

    if (this->distanceLeft - distance <= 0)
    {
        this->associated.RequestDelete();
        return;
    }
}
void Bullet::Render()
{
}
bool Bullet::Is(std::string type)
{
    return type == "Bullet";
}
int Bullet::GetDamage()
{
    return this->damage;
}

void Bullet::NotifyCollision(GameObject &other)
{
    auto bulletPtr = (Bullet*) other.GetComponent("Bullet");
    
    if (bulletPtr) //Bullet with bullet
        return;

    auto otherPtrPlayer =(PenguinBody*) other.GetComponent("PenguinBody");
    auto otherPtrCannon =(PenguinCannon*) other.GetComponent("PenguinCannon");
    auto otherPtrAlien = (Alien*) other.GetComponent("Alien");
    auto otherPtrMinion = (Minion*) other.GetComponent("Alien");

    if(this->targetsPlayer && (otherPtrPlayer)){
        associated.RequestDelete();
    }

    if(this->targetsPlayer && (otherPtrCannon)){
        associated.RequestDelete();
    }

    if(!this->targetsPlayer && (otherPtrMinion)){
        associated.RequestDelete();
    }
    if(!this->targetsPlayer && (otherPtrAlien)){
        associated.RequestDelete();
    }
}
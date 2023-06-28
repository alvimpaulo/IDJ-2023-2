#include "Bullet.hpp"
#include "Sprite.hpp"

Bullet::Bullet(GameObject &associated,
               float angle,
               float speed,
               int damage,
               float maxDistance,
               std::string sprite) : Component(associated)
{
    this->damage = damage;
    this->distanceLeft = maxDistance;

    this->speed = Vec2(speed * cos(angle), speed * sin(angle));

    auto spritePtr = new Sprite(associated, sprite);
    spritePtr->SetAngle(Vec2::rad2deg(angle));
    associated.AddComponent(spritePtr);
}
void Bullet::Update(float dt)
{
    auto srcPos = this->associated.box.GetCenter();

    Vec2 dstPos =  srcPos + (this->speed * dt);

    auto distance = Vec2::GetDistancePix(srcPos, dstPos);

    this->associated.box.SetCenter(dstPos);
    distanceLeft -= distance;

    if(this->distanceLeft - distance <= 0){
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
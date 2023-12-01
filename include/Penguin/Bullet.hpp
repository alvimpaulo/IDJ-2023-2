#pragma once
#include "Component.hpp"
#include "Vec2.hpp"

class Bullet : public Component
{
private:
    Vec2 speed;
    float distanceLeft;
    int damage;

public:
    Bullet(GameObject &associated,
           float angle,
           float speed,
           int damage,
           float maxDistance,
           std::string sprite, int frameCount, float frameTime, bool targetsPlayer);
    void Update(float dt);
    void Render();
    int GetDamage();
    void NotifyCollision (GameObject& other );
    bool targetsPlayer;
};

#pragma once
#include "Component.hpp"

class Warrior: public Component
{
public:
    Warrior(GameObject &associated);
    ~Warrior();
    void Start();
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    static Warrior *player;
    void NotifyCollision (GameObject& other );

private:
    Vec2 speed;
    float linearSpeed;
    float angle;
    int hp;

};

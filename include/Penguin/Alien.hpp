#pragma once
#include "Vec2.hpp"
#include <string>
#include "Component.hpp"

class Alien : public Component
{
private:
    Vec2 speed;
    int hp;
    int nMinions;
    std::vector<std::weak_ptr<GameObject>> minionArray;
    enum AlienState { MOVING, RESTING };
    AlienState state;
    Timer restTimer;
    Vec2 destination;

public:
    Alien(GameObject &associated, int nMinions);
    ~Alien();
    void Start();
    void Update(float dt);
    void Render();
    void NotifyCollision (GameObject& other );
    static int alienCount;
};

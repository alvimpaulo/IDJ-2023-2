#pragma once
#include "Vec2.hpp"
#include <string>
#include "Component.hpp"
#include "Timer.hpp"

class Mushroom : public Component
{
private:
    int hp;
    enum MushroomState { MOVING, RESTING };
    Timer restTimer;
    Vec2 destination;

public:
    Mushroom(GameObject &associated);
    ~Mushroom();
    void Start();
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void NotifyCollision (GameObject& other );
};



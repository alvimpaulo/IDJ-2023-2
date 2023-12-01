#pragma once
#include "Component.hpp"
#include "Timer.hpp"

class PenguinCannon : public Component
{
public:
    PenguinCannon(GameObject &associated,
                  std::weak_ptr<GameObject>
                      penguinBody);
    void Update(float dt);
    void Render();
    void Shoot();
    void NotifyCollision (GameObject& other );

private:
    std::weak_ptr<GameObject> pbody;
    float angle;
    Timer timerLastShot;
};
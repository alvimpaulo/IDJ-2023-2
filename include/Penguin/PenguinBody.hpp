#pragma once
#include <memory>
#include "Component.hpp"

class PenguinBody : public Component
{
public:
    PenguinBody(GameObject &associated, std::string type);
    ~PenguinBody();
    void Start();
    void Update(float dt);
    void Render();
    static PenguinBody *player;
    void NotifyCollision (GameObject& other );

private:
    std::weak_ptr<GameObject> pcannon;
    Vec2 speed;
    float linearSpeed;
    float angle;
    int hp;
};
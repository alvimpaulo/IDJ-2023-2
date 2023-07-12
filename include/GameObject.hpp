#pragma once
#include <vector>
#include "Rect.hpp"
#include <string>
#include <memory>

class Component;

class GameObject
{
private:
    std::vector<std::unique_ptr<Component>> components;
    bool isDead;

public:
    GameObject();
    ~GameObject();

    void Start();
    void Update(float dt);
    void Render();
    bool IsDead();
    void RequestDelete();
    void AddComponent(Component *cpt);
    void RemoveComponent(Component *cpt);
    bool IsEmpty();
    void SetAngle(double newAngle);
    double GetAngle();
    Component *GetComponent(std::string type);
    void NotifyCollision(GameObject &other);

    Rect box;
    bool started;
    float angleDeg;
};

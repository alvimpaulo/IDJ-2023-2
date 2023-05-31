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
    void AddComponent(Component* cpt);
    void RemoveComponent(Component * cpt);
    bool IsEmpty();
    Component *GetComponent(std::string type);

    Rect box;
    bool started;
};

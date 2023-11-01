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
    Vec2 scale;
    Rect box;

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
    void setScale(Vec2 scale);
    void setBoxCenter(Vec2(center));
    Rect getBox();
    void setBoxX(int x);
    void setBoxY(int y);
    void setBoxW(int w);
    void setBoxH(int h);

    bool started;
    float angleDeg;
};

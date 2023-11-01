#pragma once
#include <string>
#include "GameObject.hpp"
class Component
{
protected:
    bool isVisible;

public:
    Component(GameObject &associated);
    void setIsVisible(bool newState);
    bool getIsVisible();
    virtual ~Component();
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
    virtual bool Is(std::string type) = 0;
    virtual void Start();
    void virtual NotifyCollision(GameObject &other){};
    GameObject &associated;
};

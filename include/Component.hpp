#pragma once
#include <string>
#include "GameObject.hpp"
class Component
{
protected:
    bool isVisible;
    const std::string type;

public:
    Component(GameObject &associated, std::string type);
    void setIsVisible(bool newState);
    bool getIsVisible();
    bool toggleVisibility();
    virtual ~Component();
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
    virtual bool Is(std::string type) final;
    virtual std::string getType() final;
    virtual void Start();
    void virtual NotifyCollision(GameObject &other){};
    GameObject &associated;
};

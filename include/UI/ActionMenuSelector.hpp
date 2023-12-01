#pragma once
#include "Component.hpp"

class ActionMenuSelector : public Component
{
    enum class animationDirection
    {
        OUTWARD,
        INWARD
    };

private:
    Component *attached;
    double offset;
    animationDirection direction;
    bool isActionLocked;

public:
    ActionMenuSelector(GameObject &associated, Component* button);
    void Update(float dt);
    void Render();
    void Start();
    void setAttached(Component *newButton);
    bool getIsActionLocked();
    void setIsActionLocked(bool newState);
};

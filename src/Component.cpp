
#include "Component.hpp"
#include "GameObject.hpp"

Component::Component(GameObject &associated) : associated(associated)
{
    isVisible = false;
}

Component::~Component()
{
}

void Component::Start() {}

void Component::setIsVisible(bool newState)
{
    this->isVisible = newState;
}

bool Component::getIsVisible(){
    return isVisible;
}
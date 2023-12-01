
#include "Component.hpp"
#include "GameObject.hpp"

Component::Component(GameObject &associated, std::string type) : associated(associated), type(type)
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

bool Component::toggleVisibility(){
    isVisible = ! isVisible;
    return isVisible;
}

bool Component::Is(std::string type){
    return type == this->type;
}

std::string Component::getType(){
    return this->type;
}
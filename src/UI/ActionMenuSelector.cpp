#include "ActionMenuSelector.hpp"
#include "Sprite.hpp"

ActionMenuSelector::ActionMenuSelector(GameObject *associated, Component *button) : Component(associated, "ActionMenuSelector")
{

    offset = 0;
    direction = animationDirection::OUTWARD;
    isActionLocked = false;
    associated->setScale(Vec2(1, 1));
    auto ptrSprite = new Sprite(associated, "assets/img/UI/ActionMenuSelector.png");

    associated->AddComponent(ptrSprite);

    this->attached = button;
}
void ActionMenuSelector::Update(float dt)
{
}
void ActionMenuSelector::Render()
{
    if (attached)
    {
        auto masterBox = attached->associated->getScaledBox();
        // associated->setBoxCenter(Vec2(masterBox.x + masterBox.w / 2, masterBox.y - offset));
        associated->setBoxCenter(Vec2(masterBox.GetCenter()));
    }
}
void ActionMenuSelector::Start() {}

void ActionMenuSelector::setAttached(Component *newEntity)
{
    if (this->isActionLocked == false)
    {
        this->attached = newEntity;
    }
}

bool ActionMenuSelector::getIsActionLocked()
{
    return this->isActionLocked;
}

void ActionMenuSelector::setIsActionLocked(bool newState)
{
    this->isActionLocked = newState;
}

Component* ActionMenuSelector::getAttached(){
    return this->attached;
}
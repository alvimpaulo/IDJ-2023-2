#include "CharacterIndicator.hpp"
#include "Sprite.hpp"

CharacterIndicator::CharacterIndicator(GameObject *associated, EntityComponent *selected) : Component(associated, "CharacterIndicator"), attached(selected)
{

    offset = 40;
    direction = UP;
    isCharacterLocked = false;
    associated->setScale(Vec2(2, 2));
    auto ptrSprite = new Sprite(associated, "assets/img/UI/Indicator.png");

    associated->AddComponent(ptrSprite);
}
void CharacterIndicator::Update(float dt)
{
    switch (this->direction)
    {
    case UP:
        offset += 30 * dt;
        // std::cout << "Direction UP" << std::endl;
        break;
    case DOWN:
        offset -= 30 * dt;
        // std::cout << "Direction DOWN" << std::endl;
        break;
    }
    if (offset > 50)
    {
        direction = DOWN;
        offset = 50;
    }
    else if (offset < 40)
    {
        direction = UP;
        offset = 40;
    }
    auto masterBox = attached->associated->getScaledBox();
    associated->setBoxCenter(Vec2(masterBox.x + masterBox.w / 2, masterBox.y - offset));
}
void CharacterIndicator::Render() {}
void CharacterIndicator::Start() {}

void CharacterIndicator::setAttached(EntityComponent *newEntity)
{
    if (this->isCharacterLocked == false)
    {
        this->attached->setIsIndicated(false);
        this->attached = newEntity;
        this->attached->setIsIndicated(true);
    }
}

bool CharacterIndicator::getIsCharacterLocked()
{
    return this->isCharacterLocked;
}

void CharacterIndicator::setIsCharacterLocked(bool newState)
{
    this->isCharacterLocked = newState;
}
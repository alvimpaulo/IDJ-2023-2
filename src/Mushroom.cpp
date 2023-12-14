#include "Mushroom.hpp"
#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Collider.hpp"
#include "Game.hpp"
#include "BattleState.hpp"

Mushroom::Mushroom(GameObject *associated, int currentHp,
                   int maxHp,

                   int maxMp,
                   int currentMp,

                   int strength,
                   int wisdom,
                   int dexterity,
                   int agility,

                   int aggro, Sprite *idleSprite) : EntityComponent(associated, "Mushroom",
                                                                                                              currentHp, maxHp, maxMp, currentMp, strength, wisdom, dexterity, agility,
                                                                                                              aggro, false, Vec2(SCREEN_WIDTH - associated->getScaledBox().w, SCREEN_HEIGHT - associated->getScaledBox().h), idleSprite)
{
    setIsVisible(true);

    // auto collider = new Collider(associated);
    // this->associated->AddComponent(collider);
}

Mushroom::~Mushroom()
{
}

void Mushroom::Start()
{
}

void Mushroom::Update(float dt)
{
    EntityComponent::Update(dt);

    if (isIdle)
    {

        associated->setBoxCenter(Vec2(IdlePosition.x, IdlePosition.y));
    }
}

void Mushroom::Render()
{
}

void Mushroom::NotifyCollision(GameObject &other)
{
}

void Mushroom::physicalAttackStart(EntityComponent *target)
{
}

void Mushroom::physicalAttackEnd(EntityComponent *target)
{
    std::uniform_int_distribution<uint_least32_t> distributeDamage(1 + getStrength(), getStrength() * 4);
    auto damage = distributeDamage(generator);

    target->loseHp(damage - target->getStrength() / 2);
    this->setNewAnimation(new Animation(
        60, target->associated->getScaledBox().GetCenter(), this->IdlePosition, Mushroom::CreateRunBackSprite(associated), false, [this]
        { std::cout << "Volta do ataque começou" << std::endl; },
        [this]()
        {
            auto newIdleSprite = new Sprite(associated, "assets/img/Monsters/Mushroom/NewIdle.png", 4, 0.1, 0, 255, true, false);
            this->isIdle = true;
            this->setNewAnimation(new Animation(
                30, IdlePosition, IdlePosition, newIdleSprite, true, nullptr, nullptr,
                AnimationPhase::Phase::Idle, associated));
            BattleState::GetInstance()
                ->setRound(BattleState::Round::PlayerCharacterSelectInit);
        },
        AnimationPhase::Phase::RunBack, this->associated));
}

void Mushroom::physicalAttack(EntityComponent *target)
{
    isIdle = false;
    auto targetPosition = target->associated->getScaledBox().GetCenter() + Vec2(target->associated->getScaledBox().w / 2 + this->associated->getScaledBox().w / 2, 0);

    this->setNewAnimation(new Animation(
        30, IdlePosition, targetPosition, Mushroom::CreateRunSprite(associated), false,
        [this, target]()
        { this->physicalAttackStart(target); },
        [this, target]()
        { physicalAttackEnd(target); },
        AnimationPhase::Phase::Run, associated));
}

void Mushroom::rhythmAttackStart(EntityComponent* target){

}

void Mushroom::rhythmAttackEnd(EntityComponent* target){

}

void Mushroom::rhythmAttack(EntityComponent* target){
}


void Mushroom::useSkill(EntityComponent *target)
{
    std::uniform_int_distribution<uint_least32_t> distrib(1, 20);
    this->gainHp(distrib(generator));
    this->loseMp(5);
}
void Mushroom::defend()
{
    std::uniform_int_distribution<uint_least32_t> distrib(1, 20);
    this->gainHp(distrib(generator));
    this->loseMp(5);

}

Sprite* Mushroom::CreateIdleSprite(GameObject* associated){
    return new Sprite(associated, "assets/img/Monsters/Mushroom/NewIdle.png", 4, 0.1, 0, 255, true, false);
}

Sprite* Mushroom::CreateRunSprite(GameObject* associated){
    return new Sprite(associated, "assets/img/Monsters/Mushroom/NewIdle.png", 4, 0.1, 0, 255, true, false);
}

Sprite* Mushroom::CreateRunBackSprite(GameObject* associated){
    return new Sprite(associated, "assets/img/Monsters/Mushroom/NewIdle.png", 4, 0.1, 0, 255, true, false);
}
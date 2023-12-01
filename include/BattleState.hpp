#pragma once
#include "State.hpp"
#include "Sprite.hpp"
#include "Entities/Entity.hpp"
#include "CharacterIndicator.hpp"
#include "ManaBar.hpp"
#include "HealthBar.hpp"

class BattleState : public State
{

public:
    enum class Round
    {
        NoTurn,
        PlayerCharacterSelect,
        PlayerActionSelect,
        PlayerAction,
        EnemyActionSelect,
        EnemyAction
    };
    static BattleState *GetInstance();
    static BattleState *instance;
    void LoadAssets();
    void Update(float dt);
    void Render();
    void Start();
    void Pause();
    void Resume();
    std::shared_ptr<GameObject> getFirstObjectByComponent(std::string type);
    std::vector<std::shared_ptr<GameObject>> getAllObjectsWithComponentType(std::string type);
    EntityComponent *getSelectedCharacter();
    // Essas duas provavelmente não deveriam estar aqui.
    HealthBar *getFirstHealthBarOfEntityType(std::string type);
    ManaBar *getFirstManaBarOfEntityType(std::string type);

    void setRound(Round round);
    Round getRound();

private:
    Sprite *bgSprite;
    std::vector<EntityComponent *> characters;
    CharacterIndicator *indicator;
    int indicatedCharacterIndex;
    EntityComponent *selectedCharacter;
    BattleState();
    Round currentRound;
};

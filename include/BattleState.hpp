#pragma once
#include "State.hpp"
#include "Sprite.hpp"
#include "Entities/Entity.hpp"
#include "CharacterIndicator.hpp"

class BattleState : public State
{
private:
    Sprite *bgSprite;
    std::vector<EntityComponent *> characters;
    CharacterIndicator *indicator;
    int indicatedCharacterIndex;
    EntityComponent *selectedCharacter;
    BattleState();

public:
    static BattleState *GetInstance();
    static BattleState *instance;
    void LoadAssets();
    void Update(float dt);
    void Render();
    void Start();
    void Pause();
    void Resume();
    std::shared_ptr<GameObject> getFirstObjectByComponent(std::string type);
    EntityComponent *getSelectedCharacter();
};

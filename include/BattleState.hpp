#pragma once
#include "State.hpp"
#include "Sprite.hpp"

class BattleState : public State
{
private:
    Sprite *bgSprite;

public:
    BattleState();
    ~BattleState();
    void LoadAssets();
    void Update(float dt);
    void Render();
    void Start();
    void Pause();
    void Resume();
    std::shared_ptr<GameObject> getFirstObjectByComponent(std::string type);
    static GameObject* selectedCharecter;
    static GameObject* selectedenemy;

};

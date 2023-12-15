#pragma once
#include "../State.hpp"
#include "Entity.hpp"

class DifficultyState : public State
{

public:
    static DifficultyState *GetInstance();
    static DifficultyState *instance;
    void LoadAssets();
    void Update(float dt);
    void Render();
    void Start();
    void Pause();
    void Resume();

private:
    Sprite *bgSprite;
    DifficultyState();
    int selectedDifficulty;
    GameObject* diffSelector;
};

#pragma once
#include "../State.hpp"
#include "Entity.hpp"

class EndState : public State
{

public:
    static EndState *GetInstance(bool hasWon);
    static EndState *instance;
    void LoadAssets();
    void Update(float dt);
    void Render();
    void Start();
    void Pause();
    void Resume();

private:
    Sprite *bgSprite;
    EndState(bool hasWon);
    bool hasWon;
};

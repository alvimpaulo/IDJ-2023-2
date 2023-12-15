#pragma once
#include "../State.hpp"
#include "Entity.hpp"

class TitleState : public State
{

public:
    static TitleState *GetInstance();
    static TitleState *instance;
    void LoadAssets();
    void Update(float dt);
    void Render();
    void Start();
    void Pause();
    void Resume();

private:
    Sprite *bgSprite;
    TitleState();};

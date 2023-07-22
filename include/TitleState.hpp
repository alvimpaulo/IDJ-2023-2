#pragma once
#include "State.hpp"

class TitleState : public State
{
public:
    TitleState();
    ~TitleState();
    void LoadAssets();
    void Update(float dt);
    void Render();
    void Start();
    void Pause();
    void Resume();
};
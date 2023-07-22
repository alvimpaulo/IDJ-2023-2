#pragma once
#include "State.hpp"
#include "Sprite.hpp"
#include "Music.hpp"
#include <vector>
#include <memory>
#include "PenguinBody.hpp"
#include "TileSet.hpp"

class StageState : public State
{
private:
    TileSet *tileSet;
    Music backgroundMusic;

public:
    StageState();
    ~StageState();
    void LoadAssets();
    void Update(float dt);
    void Render();
    void Start();
    void Pause();
    void Resume();
};

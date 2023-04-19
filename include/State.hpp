#pragma once
#include "Sprite.hpp"
#include "Music.hpp"
#include <vector>
#include <memory>

class State
{
private:
    std::unique_ptr<Sprite> bg;
    Music music;
    bool quitRequested;
    std::vector<std::unique_ptr<GameObject>> objectArray;

    void Input();
    void AddObject(int mouseX, int mouseY);

public:
    State();
    ~State();
    bool QuitRequested();
    void LoadAssets();
    void Update(float dt);
    void Render();
};

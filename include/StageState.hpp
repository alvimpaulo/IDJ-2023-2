#pragma once
#include "Sprite.hpp"
#include "Music.hpp"
#include <vector>
#include <memory>
#include "PenguinBody.hpp"

class StageState
{
private:
    std::unique_ptr<Sprite> bg;
    Music music;
    bool quitRequested;
    std::vector<std::shared_ptr<GameObject>> objectArray;
    bool started;

public:
    StageState();
    ~StageState();
    bool QuitRequested();
    void LoadAssets();
    void Update(float dt);
    void Render();
    void Start();

    std::weak_ptr<GameObject> AddObject(std::shared_ptr<GameObject> go);
    std::weak_ptr<GameObject> GetObjectPtr(GameObject *go);
};

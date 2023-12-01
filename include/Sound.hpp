#pragma once
#include <SDL2/SDL_mixer.h>
#include <string>
#include "GameObject.hpp"
#include "Component.hpp"

class Sound : public Component
{
private:
    Mix_Chunk *chunk;
    int channel;

public:
    Sound(GameObject &associated);
    ~Sound();
    void Play(int times = 1);
    void Stop();
    void Open(std::string file);
    bool IsOpen();
    void Update(float dt);
    void Render();
    bool IsPlaying;
};

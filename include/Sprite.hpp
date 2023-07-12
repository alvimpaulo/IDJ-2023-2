#pragma once
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Component.hpp"
#include "Timer.hpp"

class Sprite : public Component
{
private:
    SDL_Texture *texture;
    int width;
    int height;
    SDL_Rect clipRect;
    Vec2 scale;
    int frameCount;
    int currentFrame;
    float timeElapsed;
    float frameTime;
    Timer selfDesctructCount;
    float secondsToSelfDestruct;

public:
    Sprite(GameObject &associated);
    Sprite(GameObject &associated, std::string file, int frameCount = 1,
           float frameTime = 1, float secondsToSelfDestruct = 0);
    ~Sprite();

    void Open(std::string file);
    void SetClip(int x, int y, int w, int h);
    void Render(float x, float y, float w, float h);
    void Render();
    int GetWidth();
    int GetHeight();
    bool IsOpen();
    bool Is(std::string type);
    void Update(float dt);
    void SetScaleX(float scaleX, float scaleY);
    Vec2 GetScale();
    void SetFrame(int frame);
    void SetFrameCount(int frameCount);
    void SetFrameTime(float frameTime);
};

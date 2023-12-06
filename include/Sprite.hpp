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
    int opacity;
    SDL_Rect clipRect;
    int frameCount;
    int currentFrame;
    float timeElapsed;
    float frameTime;
    Timer selfDesctructCount;
    float secondsToSelfDestruct;
    bool flipHorizontal;
    bool flipVertical;
    Vec2 scale;
    std::string file;

public:
    Sprite(GameObject *associated);
    Sprite(GameObject *associated, std::string file, int frameCount = 1,
           float frameTime = 1, float secondsToSelfDestruct = 0, int opacity = 255, bool flipHorizontal = false, bool flipVertical = false);
    ~Sprite();
    Sprite* CreateCopy();

    void Open(std::string file);
    void SetClip(int x, int y, int w, int h);
    void Render(float x, float y, float w, float h);
    void Render();
    bool IsOpen();
    void Update(float dt);
    void SetFrame(int frame);
    void SetFrameCount(int frameCount);
    void SetFrameTime(float frameTime);
    void setOpacity(int newOpacity);
    int getFrameCount();
    int getSingleFrameWidth();
    int getWidth();
    void setScale(Vec2 newScale);
    Vec2 getScale();
    int getCurrentFrame() const;
    void setCurrentFrame(int currentFrame_);

    int getFrameCount() const;
    void setFrameCount(int frameCount_);

    void setTimeElapsed(float timeElapsed_);
};

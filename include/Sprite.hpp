#pragma once
#include <string>
#include <SDL2/SDL.h>  
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Component.hpp"

class Sprite : public Component
{
private:
    SDL_Texture *texture;
    int width;
    int height;
    SDL_Rect clipRect;

public:
    Sprite(GameObject &associated);
    Sprite(GameObject &associated, std::string file);
    ~Sprite();

    void Open(std::string file);
    void SetClip(int x, int y, int w, int h);
    void Render(float x, float y, float w, float h);
    void Render();
    int GetWidth();
    int getHeight();
    bool IsOpen();
    bool Is(std::string type);
    void Update(float dt);
};

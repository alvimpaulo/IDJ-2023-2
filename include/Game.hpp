#pragma once
#include <SDL2/SDL.h>
#include <string>
#include "State.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

class Game
{
public:
    ~Game();
    void Run();
    SDL_Renderer *GetRenderer();
    State &GetState();
    static Game &GetInstance();

private:
    Game(std::string title, int width, int height);
    static Game *instance;
    SDL_Window *window;
    SDL_Renderer *renderer;
    State *state;
};
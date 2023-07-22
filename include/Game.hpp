#pragma once
#include <SDL2/SDL.h>
#include <string>
#include "State.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <stack>
#include <memory>

#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 1024

class Game
{
public:
    ~Game();
    void Run();
    SDL_Renderer *GetRenderer();
    State *GetCurrentState();
    static Game &GetInstance();
    float GetDeltaTime();
    void Push(State *state);

private:
    Game(std::string title, int width, int height);
    void CalculateDeltaTime();

    static Game *instance;
    SDL_Window *window;
    SDL_Renderer *renderer;
    int frameStart;
    float dt;
    State *storedState;
    std::stack<State *> stateStack;
};
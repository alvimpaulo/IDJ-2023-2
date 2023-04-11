#include "State.hpp"

State::State()
{
    this->quitRequested = false;
    this->music = Music();
    this->bg = Sprite();
}

void State::LoadAssets()
{
    this->music.Open("assets/audio/stageState.ogg");
    this->music.Play();
    this->bg.Open("assets/img/ocean.jpg");
}

void State::Update(float dt)
{
    if (SDL_QuitRequested() == true)
    {
        this->quitRequested = true;
    }
}

void State::Render()
{
    this->bg.Render(0, 0);
}

bool State::QuitRequested()
{
    return quitRequested;
}

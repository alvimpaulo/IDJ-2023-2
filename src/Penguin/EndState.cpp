#include "EndState.hpp"
#include "GameData.hpp"
#include "Sprite.hpp"
#include "InputManager.hpp"
#include "Penguin/TitleState.hpp"
#include "Game.hpp"

EndState::EndState()
{
    auto *object = new GameObject();

    if (GameData::playerVictory)
    {
        object->AddComponent(new Sprite(*object, "assets/img/Penguin/win.jpg"));
        backgroundMusic.Open("assets/audio/endStateWin.ogg");
    }
    else
    {
        object->AddComponent(new Sprite(*object, "assets/img/Penguin/lose.jpg"));
        backgroundMusic.Open("assets/audio/endStateLose.ogg");
    }

    AddObject(object);
}
EndState::~EndState()
{
}
void EndState::LoadAssets()
{

}
void EndState::Update(float dt)
{
    quitRequested = InputManager::GetInstance().QuitRequested() || InputManager::GetInstance().KeyPress(ESCAPE_KEY);
    if(quitRequested){
        quitRequested = true;
        return;
    }
    auto playAgain = InputManager::GetInstance().KeyPress(SDLK_SPACE);

    if (playAgain)
    {
        popRequested = true;
        Game::GetInstance().Push(new TitleState());
    }
    UpdateArray(dt);
}
void EndState::Render()
{
    RenderArray();
}
void EndState::Start()
{
    StartArray();
}
void EndState::Pause()
{
}
void EndState::Resume()
{
}
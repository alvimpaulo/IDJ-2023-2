#include "Penguin/TitleState.hpp"
#include "Sprite.hpp"
#include "Penguin/StageState.hpp"
#include "Game.hpp"
#include "InputManager.hpp"
#include "CameraFollower.hpp"
#include "Game.hpp"
#include "Camera.hpp"
#include "Text.hpp"

TitleState::TitleState()
{
    GameObject *tileObject = new GameObject();

    tileObject->AddComponent(new CameraFollower(*tileObject));
    auto sprite = new Sprite(*tileObject, "assets/img/Penguin/title.jpg");
    tileObject->AddComponent(sprite);
    this->AddObject(tileObject);

    auto *textObject = new GameObject();
    std::string textString = "Aperte Barra de Espasso";
    SDL_Color textColor = {0, 0, 0, 0xff};
    auto *textComponent = new Text(*textObject, "assets/font/Call me maybe.ttf", 14, Text::BLENDED, textString, textColor);
    textObject->AddComponent(textComponent);
    AddObject(textObject);

    textObject->setBoxCenter(Vec2(480.f, 500.f));
}
TitleState::~TitleState()
{
}
void TitleState::LoadAssets()
{
}
void TitleState::Update(float dt)
{
    if (InputManager::GetInstance().QuitRequested() || InputManager::GetInstance().KeyPress(SDLK_ESCAPE))
    {
        this->quitRequested = true;
    }

    if (InputManager::GetInstance().KeyPress(SDLK_SPACE))
    {
        auto stage = new StageState();
        Game::GetInstance().Push(stage);
    }
}
void TitleState::Render()
{
    RenderArray();
}
void TitleState::Start()
{
    StartArray();
}
void TitleState::Pause()
{
}
void TitleState::Resume()
{

    auto sprite = (Sprite *)this->objectArray[0]->GetComponent("Sprite");
    sprite->SetClip(0, 0, sprite->associated.getScaledBox().w, sprite->associated.getScaledBox().h);
    Camera::Unfollow();

    auto text = (Text *)this->objectArray[1]->GetComponent("Text");
    this->objectArray[1]->setBoxCenter(Vec2(480.f, 500.f));

    Camera::pos = Vec2(0, 0);
}
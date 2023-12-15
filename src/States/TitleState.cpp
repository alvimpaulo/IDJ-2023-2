
#include "Vec2.hpp"
#include "Sound.hpp"
#include <memory>
#include "my_utility.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "CameraFollower.hpp"
#include "Collider.hpp"
#include "Game.hpp"
#include "CameraFollower.hpp"
#include "GameData.hpp"
#include <random>
#include "TitleState.hpp"
#include "Mushroom.hpp"
#include "Warrior.hpp"
#include "ActionMenu.hpp"
#include "HealthBar.hpp"
#include "ManaBar.hpp"
#include "AttackButton.hpp"
#include "DefendButton.hpp"
#include "SkillButton.hpp"
#include "UI/CharacterIndicator.hpp"
#include "BlinkingText.hpp"
#include "BattleState.hpp"

TitleState *TitleState::instance = nullptr;

TitleState::TitleState()
{
	this->quitRequested = false;
	this->started = false;

	auto bgObject = new GameObject();
	auto bgFollower = new CameraFollower(bgObject);
	bgObject->AddComponent(bgFollower);
	bgSprite = new Sprite(bgObject);
	bgObject->AddComponent(bgSprite);
	AddObject(bgObject);

	auto blinkTextObj = new GameObject();
	auto blinkTextPtr = new BlinkingText(blinkTextObj, Vec2(200, 540), 3, "Pressione barra de espaco para continuar...");
	blinkTextObj->AddComponent(blinkTextPtr);
	AddObject(blinkTextObj);
}

void TitleState::LoadAssets()
{
	if (bgSprite)
	{
		bgSprite->Open("assets/img/Menu/Introducao.png");
	}
}

void TitleState::Start()
{
	started = true;
	this->LoadAssets();

	StartArray();
}

void TitleState::Update(float dt)
{

	if (InputManager::GetInstance().QuitRequested())
	{
		this->quitRequested = true;
	}

	if(InputManager::GetInstance().KeyPress(SDLK_SPACE)){
		popRequested = true;
	}

	UpdateArray(dt);

	for (size_t i = 0; i < this->objectArray.size(); i++)
	{
		if (objectArray[i]->IsDead())
		{
			if (auto soundPtr = (Sound *)objectArray[i]->GetComponent("Sound"))
			{
				if (!soundPtr->IsPlaying)
				{
					objectArray[i].reset();
				}
			}

			objectArray.erase(objectArray.begin() + i);
		}
	}
}

void TitleState::Render()
{
	this->RenderArray();
}

void TitleState::Pause()
{
}

void TitleState::Resume()
{
}

TitleState *TitleState::GetInstance()
{
	if (TitleState::instance == nullptr)
	{
		TitleState::instance = new TitleState();
		return TitleState::instance;
	}
	else
	{
		return TitleState::instance;
	}
}
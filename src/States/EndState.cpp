
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
#include "EndState.hpp"
#include "Mushroom.hpp"
#include "Warrior.hpp"
#include "ActionMenu.hpp"
#include "HealthBar.hpp"
#include "ManaBar.hpp"
#include "AttackButton.hpp"
#include "DefendButton.hpp"
#include "SkillButton.hpp"
#include "UI/CharacterIndicator.hpp"

EndState *EndState::instance = nullptr;

EndState::EndState()
{
	this->quitRequested = false;
	this->started = false;

	auto bgObject = new GameObject();
	auto bgFollower = new CameraFollower(bgObject);
	bgObject->AddComponent(bgFollower);
	bgSprite = new Sprite(bgObject);
	bgObject->AddComponent(bgSprite);
	AddObject(bgObject);
}

void EndState::LoadAssets()
{
	if (bgSprite)
	{
		bgSprite->Open("assets/img/background.png");
	}
}

void EndState::Start()
{
	started = true;
	this->LoadAssets();

	StartArray();
}

void EndState::Update(float dt)
{

	if (InputManager::GetInstance().QuitRequested())
	{
		this->quitRequested = true;
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

void EndState::Render()
{
	this->RenderArray();
}

void EndState::Pause()
{
}

void EndState::Resume()
{
}

EndState *EndState::GetInstance()
{
	if (EndState::instance == nullptr)
	{
		EndState::instance = new EndState();
		return EndState::instance;
	}
	else
	{
		return EndState::instance;
	}
}
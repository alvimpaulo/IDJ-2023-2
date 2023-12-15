
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
#include "DifficultyState.hpp"
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
#include "TitleState.hpp"

DifficultyState *DifficultyState::instance = nullptr;

DifficultyState::DifficultyState()
{
	this->quitRequested = false;
	this->started = false;
	this->selectedDifficulty = 0;

	auto bgObject = new GameObject();
	auto bgFollower = new CameraFollower(bgObject);
	bgObject->AddComponent(bgFollower);
	bgSprite = new Sprite(bgObject);
	bgObject->AddComponent(bgSprite);
	AddObject(bgObject);

	// auto blinkTextObj = new GameObject();
	// auto blinkTextPtr = new BlinkingText(blinkTextObj, Vec2(560, 540), 3, "Pressione qualquer tecla...");
	// blinkTextObj->AddComponent(blinkTextPtr);
	// AddObject(blinkTextObj);

	diffSelector = new GameObject();
	auto diffPtr = new Sprite(diffSelector, "assets/img/Menu/main-menu/Indicator.png");
	diffSelector->AddComponent(diffPtr);
	AddObject(diffSelector);
}

void DifficultyState::LoadAssets()
{
	if (bgSprite)
	{
		bgSprite->Open("assets/img/Menu/main-menu/main-menu.png");
	}
}

void DifficultyState::Start()
{
	started = true;
	this->LoadAssets();

	StartArray();
}

void DifficultyState::Update(float dt)
{

	if (InputManager::GetInstance().QuitRequested())
	{
		this->quitRequested = true;
	}

	if (InputManager::GetInstance().KeyPress(SDLK_UP))
	{
		selectedDifficulty = std::max(0, selectedDifficulty - 1);
	}

	if (InputManager::GetInstance().KeyPress(SDLK_DOWN))
	{
		selectedDifficulty = std::min(2, selectedDifficulty + 1);
	}

	if (InputManager::GetInstance().KeyPress(SDLK_RETURN))
	{
		auto introState = TitleState::GetInstance();
		BattleState *battleState;
		switch (selectedDifficulty)
		{
		case 0:
			battleState = BattleState::GetInstance(8, 5, 200);
			break;
		case 1:
			battleState = BattleState::GetInstance(4, 3, 100);
			break;
		case 2:
			battleState = BattleState::GetInstance(3, 1, 50);
			break;
		default:
			break;
		}
		Game::GetInstance().Push(battleState);

		Game::GetInstance().Push(introState);
		requestPop();
	}

	if (diffSelector)
	{
		switch (selectedDifficulty)
		{
		case 0:
			this->diffSelector->setBoxCenter(Vec2(427, 401));
			break;
		case 1:
			this->diffSelector->setBoxCenter(Vec2(427, 461));
			break;
		case 2:
			this->diffSelector->setBoxCenter(Vec2(427, 522));
			break;
		default:
			this->diffSelector->setBoxCenter(Vec2(427, 401));
			break;
		}
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

void DifficultyState::Render()
{
	this->RenderArray();
}

void DifficultyState::Pause()
{
}

void DifficultyState::Resume()
{
}

DifficultyState *DifficultyState::GetInstance()
{
	if (DifficultyState::instance == nullptr)
	{
		DifficultyState::instance = new DifficultyState();
		return DifficultyState::instance;
	}
	else
	{
		return DifficultyState::instance;
	}
}
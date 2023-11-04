
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
#include "EndState.hpp"
#include <random>
#include "BattleState.hpp"
#include "Mushroom.hpp"
#include "Warrior.hpp"
#include "ActionMenu.hpp"
#include "Button.hpp"
#include "HealthBar.hpp"
#include "ManaBar.hpp"
#include "AttackButton.hpp"
#include "DefendButton.hpp"
#include "SkillButton.hpp"

BattleState::BattleState()
{
	this->quitRequested = false;
	this->started = false;

	auto mapObject = new GameObject();

	auto bgObject = new GameObject();
	auto bgFollower = new CameraFollower(*bgObject);
	bgObject->AddComponent(bgFollower);
	bgSprite = new Sprite(*bgObject);
	bgObject->AddComponent(bgSprite);
	AddObject(bgObject);

	auto menuObj = new GameObject();
	auto menu = ActionMenu(*menuObj);

	auto actionMenuObj = new GameObject();
	auto actionMenu = new ActionMenu(*actionMenuObj);
	actionMenuObj->AddComponent(actionMenu);
	this->AddObject(actionMenuObj);
	actionMenu->setVisible(true);

	auto attackButtonObj = new GameObject();
	auto attackButton = new AttackButton(*attackButtonObj);
	attackButton->setIsVisible(true);
	attackButtonObj->AddComponent(attackButton);
	this->AddObject(attackButtonObj);

	auto defendButtonObj = new GameObject();
	auto defendButton = new DefendButton(*defendButtonObj);
	defendButtonObj->AddComponent(defendButton);
	this->AddObject(defendButtonObj);

	auto skillButtonObj = new GameObject();
	auto skillButton = new SkillButton(*skillButtonObj);
	skillButtonObj->AddComponent(skillButton);
	this->AddObject(skillButtonObj);

	auto mushroomObj = new GameObject();
	auto mushroom = new Mushroom(*mushroomObj, 100, 100, 100, 100, 1, 10, 5, 1, 50);
	mushroomObj->AddComponent(mushroom);
	this->AddObject(mushroomObj);

	auto mushroomHealthBarObj = new GameObject();
	auto mushroomHealthBar = new HealthBar(*mushroomHealthBarObj, *mushroom);
	mushroomHealthBarObj->AddComponent(mushroomHealthBar);
	this->AddObject(mushroomHealthBarObj);

	auto mushroomManaBarObj = new GameObject();
	auto mushroomManaBar = new ManaBar(*mushroomManaBarObj, *mushroom);
	mushroomManaBarObj->AddComponent(mushroomManaBar);
	this->AddObject(mushroomManaBarObj);

	auto warriorObj = new GameObject();
	auto warrior = new Warrior(*warriorObj, 100, 100, 100, 100, 15, 1, 10, 10, 50);
	warriorObj->AddComponent(warrior);
	this->AddObject(warriorObj);

	auto warriorHealthBarObj = new GameObject();
	auto warriorHealthBar = new HealthBar(*warriorHealthBarObj, *warrior);
	warriorHealthBarObj->AddComponent(warriorHealthBar);
	this->AddObject(warriorHealthBarObj);

	auto warriorManaBarObj = new GameObject();
	auto warriorManaBar = new ManaBar(*warriorManaBarObj, *warrior);
	warriorManaBarObj->AddComponent(warriorManaBar);
	this->AddObject(warriorManaBarObj);
}

BattleState::~BattleState()
{
}

void BattleState::LoadAssets()
{
	if (bgSprite)
	{
		bgSprite->Open("assets/img/background.png");
	}
}

void BattleState::Start()
{
	started = true;
	this->LoadAssets();

	StartArray();
}

void BattleState::Update(float dt)
{
	auto mouseX = InputManager::GetInstance().GetMouseX();
	auto mouseY = InputManager::GetInstance().GetMouseY();
	// camera update
	// Camera::Update(dt);

	std::vector<std::pair<std::shared_ptr<GameObject>, Collider *>> colliders;

	if (InputManager::GetInstance().QuitRequested() || InputManager::GetInstance().KeyPress(ESCAPE_KEY))
	{
		this->quitRequested = true;
	}
	if (InputManager::GetInstance().KeyPress(SDLK_SPACE))
	{
		auto mushroomComponent = this->getFirstObjectByComponent("Mushroom");
		if (mushroomComponent)
		{
			auto mushroomPtr = (Mushroom *)mushroomComponent->GetComponent("Mushroom");
			mushroomPtr->setIsVisible(!(mushroomPtr->getIsVisible()));
		}
	}

	if (InputManager::GetInstance().KeyPress(SDLK_RIGHT))
	{
		auto mushroom = this->getFirstObjectByComponent("Mushroom");
		if (mushroom)
		{
			auto mushroomPtr = (Mushroom *)mushroom->GetComponent("Mushroom");
			mushroomPtr->loseHp(10);
			;
		}
	}

	if (InputManager::GetInstance().KeyPress(SDLK_LEFT))
	{
		auto warrior = this->getFirstObjectByComponent("Warrior");
		if (warrior)
		{
			auto warriorPtr = (Warrior *)warrior->GetComponent("Warrior");
			warriorPtr->loseHp(10);
			;
		}
	}

	if (InputManager::GetInstance().MousePress(SDL_BUTTON_LEFT))
	{
		auto attackButtonobj = this->getFirstObjectByComponent("AttackButton");
		if (attackButtonobj->getBox().Contains({mouseX, mouseY}))
		{
			auto mushroomObj = this->getFirstObjectByComponent("Mushroom");
			auto warriorObj = this->getFirstObjectByComponent("Warrior");
			auto mushroomPtr = (Mushroom *)mushroomObj->GetComponent("Mushroom");
			auto warriorPtr = (Warrior *)warriorObj->GetComponent("Warrior");
			mushroomPtr->gainHp(100);
			warriorPtr->gainHp(100);
		}

		auto defendButtonObj = this->getFirstObjectByComponent("DefendButton");
		if (defendButtonObj->getBox().Contains({mouseX, mouseY}))
		{
			auto mushroomObj = this->getFirstObjectByComponent("Mushroom");
			auto warriorObj = this->getFirstObjectByComponent("Warrior");
			auto mushroomPtr = (Mushroom *)mushroomObj->GetComponent("Mushroom");
			auto warriorPtr = (Warrior *)warriorObj->GetComponent("Warrior");
			mushroomPtr->gainMp(100);
			warriorPtr->gainMp(100);
		}
	}

	if (InputManager::GetInstance().KeyPress(SDLK_DOWN))
	{
		auto mushroom = this->getFirstObjectByComponent("Mushroom");
		if (mushroom)
		{
			auto mushroomPtr = (Mushroom *)mushroom->GetComponent("Mushroom");
			mushroomPtr->loseMp(10);
			;
		}
	}

	if (InputManager::GetInstance().KeyPress(SDLK_UP))
	{
		auto warrior = this->getFirstObjectByComponent("Warrior");
		if (warrior)
		{
			auto warriorPtr = (Warrior *)warrior->GetComponent("Warrior");
			warriorPtr->loseMp(10);
			;
		}
	}

	UpdateArray(dt);

	for (size_t i = 0; i < this->objectArray.size(); i++)
	{
		if (auto colliderPtr = (Collider *)objectArray[i]->GetComponent("Collider"))
		{
			colliders.push_back({objectArray[i], colliderPtr});
		}
	}

	for (size_t i = 0; i < colliders.size(); i++)
	{
		for (size_t j = i + 1; j < colliders.size(); j++)
		{
			if (Collider::IsColliding(colliders[i].second->box, colliders[j].second->box, colliders[i].first->angleDeg, colliders[j].first->angleDeg))
			{
				colliders[i].first->NotifyCollision(*colliders[j].first);
				colliders[j].first->NotifyCollision(*colliders[i].first);
			}
		}
	}

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

void BattleState::Render()
{
	this->RenderArray();
}

void BattleState::Pause()
{
}

void BattleState::Resume()
{
}

std::shared_ptr<GameObject> BattleState::getFirstObjectByComponent(std::string type)
{
	for (size_t i = 0; i < objectArray.size(); i++)
	{
		if (objectArray[i]->GetComponent(type))
		{
			return objectArray[i];
		}
	}

	return nullptr;
}
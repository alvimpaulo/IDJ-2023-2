
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
#include "GreenBar.hpp"

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
	auto attackButton = new Button(*attackButtonObj, Button::ATTACK);
	attackButton->setIsVisible(true);
	attackButtonObj->AddComponent(attackButton);
	this->AddObject(attackButtonObj);

	auto defendButtonObj = new GameObject();
	auto defendButton = new Button(*defendButtonObj, Button::DEFEND);
	defendButtonObj->AddComponent(defendButton);
	this->AddObject(defendButtonObj);

	auto skillButtonObj = new GameObject();
	auto skillButton = new Button(*skillButtonObj, Button::SKILL);
	skillButtonObj->AddComponent(skillButton);
	this->AddObject(skillButtonObj);

	auto mushroomObj = new GameObject();
	auto mushroom = new Mushroom(*mushroomObj, 100, 100, 100, 100, 1, 10, 5, 1, 50);
	mushroomObj->AddComponent(mushroom);
	this->AddObject(mushroomObj);

	auto healthBarObj2 = new GameObject();
	auto healthBar2 = new HealthBar(*healthBarObj2, *mushroom);
	healthBarObj2->AddComponent(healthBar2);
	this->AddObject(healthBarObj2);

	auto warriorObj = new GameObject();
	auto warrior = new Warrior(*warriorObj, 100, 100, 100, 100, 15, 1, 10, 10, 50);
	warriorObj->AddComponent(warrior);
	this->AddObject(warriorObj);

	auto healthBarObj1 = new GameObject();
	auto healthBar1 = new HealthBar(*healthBarObj1, *warrior);
	healthBarObj1->AddComponent(healthBar1);
	this->AddObject(healthBarObj1);
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
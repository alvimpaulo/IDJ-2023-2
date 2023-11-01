
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
	attackButton->isVisible = true;
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
	auto mushroom = new Mushroom(*mushroomObj);
	auto mushroomSprite = (Sprite *)mushroom->associated.GetComponent("Sprite");
	mushroomObj->setBoxCenter(Vec2(SCREEN_WIDTH - (mushroomSprite->GetScaledWidth()), SCREEN_HEIGHT - mushroomSprite->GetScaledHeight() - 100));
	mushroomObj->AddComponent(mushroom);
	this->AddObject(mushroomObj);

	auto warriorObj = new GameObject();
	auto warrior = new Warrior(*warriorObj);
	warriorObj->AddComponent(warrior);
	this->AddObject(warriorObj);
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
	Camera::Update(dt);

	std::vector<std::pair<std::shared_ptr<GameObject>, Collider *>> colliders;

	if (InputManager::GetInstance().QuitRequested() || InputManager::GetInstance().KeyPress(ESCAPE_KEY))
	{
		this->quitRequested = true;
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
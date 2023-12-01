
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
#include "UI/CharacterIndicator.hpp"
#include "Ranger.hpp"

BattleState *BattleState::instance = nullptr;

BattleState::BattleState() : indicatedCharacterIndex(0), selectedCharacter(nullptr)
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

	auto attackButtonObj = new GameObject();
	auto attackButton = new AttackButton(*attackButtonObj, actionMenu);
	attackButtonObj->AddComponent(attackButton);
	this->AddObject(attackButtonObj);

	auto defendButtonObj = new GameObject();
	auto defendButton = new DefendButton(*defendButtonObj, actionMenu);
	defendButtonObj->AddComponent(defendButton);
	this->AddObject(defendButtonObj);

	auto skillButtonObj = new GameObject();
	auto skillButton = new SkillButton(*skillButtonObj, actionMenu);
	skillButtonObj->AddComponent(skillButton);
	this->AddObject(skillButtonObj);

	//------------------------------------- MUSHROOM -----------------------------------------------------

	auto mushroomObj = new GameObject();
	auto mushroom = new Mushroom(*mushroomObj, 100, 100, 100, 100, 1, 10, 5, 1, 50);
	mushroomObj->AddComponent(mushroom);
	this->AddObject(mushroomObj);

	auto mushroomHealthBarObj = new GameObject();
	auto mushroomHealthBar = new HealthBar(*mushroomHealthBarObj, mushroom);
	mushroomHealthBarObj->AddComponent(mushroomHealthBar);
	this->AddObject(mushroomHealthBarObj);

	auto mushroomManaBarObj = new GameObject();
	auto mushroomManaBar = new ManaBar(*mushroomManaBarObj, mushroom);
	mushroomManaBarObj->AddComponent(mushroomManaBar);
	this->AddObject(mushroomManaBarObj);
	//------------------------------------- MUSHROOM -----------------------------------------------------

	//------------------------------------- RANGER -----------------------------------------------------

	auto rangerObj = new GameObject();
	auto ranger = new Ranger(*rangerObj, 100, 100, 100, 100, 15, 1, 10, 10, 50);
	rangerObj->AddComponent(ranger);
	this->AddObject(rangerObj);

	auto rangerHealthBarObj = new GameObject();
	auto rangerHealthBar = new HealthBar(*rangerHealthBarObj, ranger);
	rangerHealthBarObj->AddComponent(rangerHealthBar);
	this->AddObject(rangerHealthBarObj);

	auto rangerManaBarObj = new GameObject();
	auto rangerManaBar = new ManaBar(*rangerManaBarObj, ranger);
	rangerManaBarObj->AddComponent(rangerManaBar);
	this->AddObject(rangerManaBarObj);

	characters.push_back(ranger);
	//------------------------------------- RANGER -----------------------------------------------------

	//------------------------------------- WARRIOR -----------------------------------------------------

	auto warriorObj = new GameObject();
	auto warrior = new Warrior(*warriorObj, 100, 100, 100, 100, 15, 1, 10, 10, 50);
	warriorObj->AddComponent(warrior);
	this->AddObject(warriorObj);

	auto warriorHealthBarObj = new GameObject();
	auto warriorHealthBar = new HealthBar(*warriorHealthBarObj, warrior);
	warriorHealthBarObj->AddComponent(warriorHealthBar);
	this->AddObject(warriorHealthBarObj);

	auto warriorManaBarObj = new GameObject();
	auto warriorManaBar = new ManaBar(*warriorManaBarObj, warrior);
	warriorManaBarObj->AddComponent(warriorManaBar);
	this->AddObject(warriorManaBarObj);

	characters.push_back(warrior);
	//------------------------------------- WARRIOR -----------------------------------------------------

	auto indicatorObj = new GameObject();
	auto indicator = new CharacterIndicator(*indicatorObj, ranger);
	indicatorObj->AddComponent(indicator);
	this->AddObject(indicatorObj);
	this->indicator = indicator;
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

	if (InputManager::GetInstance().QuitRequested())
	{
		this->quitRequested = true;
	}

	if (InputManager::GetInstance().KeyPress(UP_ARROW_KEY))
	{
		if (indicator->getIsCharacterLocked() == false)
		{
			auto characterHealthBar = getFirstHealthBarOfEntityType(characters[indicatedCharacterIndex]->getType());
			if(characterHealthBar){
				characterHealthBar->setIsVisible(false);
			}

			auto characterManaBar = getFirstManaBarOfEntityType(characters[indicatedCharacterIndex]->getType());
			if(characterManaBar){
				characterManaBar->setIsVisible(false);
			}
			
			indicatedCharacterIndex = std::max(indicatedCharacterIndex - 1, 0);
			indicator->setAttached(characters[indicatedCharacterIndex]);
		}
	}
	if (InputManager::GetInstance().KeyPress(DOWN_ARROW_KEY))
	{
		if (indicator->getIsCharacterLocked() == false)
		{
			auto characterHealthBar = getFirstHealthBarOfEntityType(characters[indicatedCharacterIndex]->getType());
			if(characterHealthBar){
				characterHealthBar->setIsVisible(false);
			}

			auto characterManaBar = getFirstManaBarOfEntityType(characters[indicatedCharacterIndex]->getType());
			if(characterManaBar){
				characterManaBar->setIsVisible(false);
			}
			
			indicatedCharacterIndex = std::min(indicatedCharacterIndex + 1, (int)characters.size() - 1);
			indicator->setAttached(characters[indicatedCharacterIndex]);
		}
	}
	if (InputManager::GetInstance().KeyPress(SDLK_RETURN))
	{
		this->selectedCharacter = characters[indicatedCharacterIndex];
		indicator->setIsCharacterLocked(true);
	}
	if (InputManager::GetInstance().KeyPress(SDLK_BACKSPACE))
	{
		this->selectedCharacter = nullptr;
		indicator->setIsCharacterLocked(false);
	}

	if (InputManager::GetInstance().KeyPress(SDLK_SPACE))
	{

		auto mushroomHealthBar = getFirstHealthBarOfEntityType("Mushroom");

		if (mushroomHealthBar)
			mushroomHealthBar->toggleVisibility();

		auto mushroomManaBar = getFirstManaBarOfEntityType("Mushroom");

		if (mushroomManaBar)
			mushroomManaBar->toggleVisibility();
	}

	if (InputManager::GetInstance().KeyPress(SDLK_KP_1))
	{
		auto mushroom = this->getFirstObjectByComponent("Mushroom");
		if (mushroom)
		{
			auto mushroomPtr = (Mushroom *)mushroom->GetComponent("Mushroom");
			mushroomPtr->loseHp(10);
		}
	}

	if (InputManager::GetInstance().KeyPress(SDLK_KP_2))
	{
		auto warrior = this->getFirstObjectByComponent("Warrior");
		if (warrior)
		{
			auto warriorPtr = (Warrior *)warrior->GetComponent("Warrior");
			warriorPtr->loseHp(10);
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

	if (InputManager::GetInstance().KeyPress(SDLK_KP_3))
	{
		auto mushroom = this->getFirstObjectByComponent("Mushroom");
		if (mushroom)
		{
			auto mushroomPtr = (Mushroom *)mushroom->GetComponent("Mushroom");
			mushroomPtr->loseMp(10);
			;
		}
	}

	if (InputManager::GetInstance().KeyPress(SDLK_KP_4))
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

std::vector<std::shared_ptr<GameObject>> BattleState::getAllObjectsWithComponentType(std::string type)
{
	std::vector<std::shared_ptr<GameObject>> returnVector;

	for (size_t i = 0; i < objectArray.size(); i++)
	{
		if (objectArray[i]->GetComponent(type))
		{
			returnVector.push_back(objectArray[i]);
		}
	}

	return returnVector;
}

BattleState *BattleState::GetInstance()
{
	if (BattleState::instance == nullptr)
	{
		BattleState::instance = new BattleState();
		return BattleState::instance;
	}
	else
	{
		return BattleState::instance;
	}
}

EntityComponent *BattleState::getSelectedCharacter()
{
	return this->selectedCharacter;
}

HealthBar *BattleState::getFirstHealthBarOfEntityType(std::string type)
{
	auto healthBars = this->getAllObjectsWithComponentType("HealthBar");

	for (size_t i = 0; i < healthBars.size(); i++)
	{
		auto healthBarPtr = (HealthBar *)healthBars[i]->GetComponent("HealthBar");
		if (healthBarPtr->getMasterEntity()->Is(type))
		{
			return healthBarPtr;
		}
	}

	return nullptr;
}
ManaBar *BattleState::getFirstManaBarOfEntityType(std::string type)
{
	auto manaBars = this->getAllObjectsWithComponentType("ManaBar");

	for (size_t i = 0; i < manaBars.size(); i++)
	{
		auto manaBarPtr = (ManaBar *)manaBars[i]->GetComponent("ManaBar");
		if (manaBarPtr->getMasterEntity()->Is(type))
		{
			return manaBarPtr;
		}
	}

	return nullptr;
}
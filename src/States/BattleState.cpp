
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
#include "Bargudin.hpp"
#include "ActionMenu.hpp"
#include "HealthBar.hpp"
#include "ManaBar.hpp"
#include "AttackButton.hpp"
#include "DefendButton.hpp"
#include "SkillButton.hpp"
#include "UI/CharacterIndicator.hpp"
#include "EndState.hpp"
#include "Porco.hpp"

BattleState *BattleState::instance = nullptr;

BattleState::BattleState() : indicatedCharacterIndex(0), selectedCharacter(nullptr)
{
	this->quitRequested = false;
	this->started = false;
	this->balls = std::deque<GameObject *>(0);

	auto mapObject = new GameObject();

	auto bgObject = new GameObject();
	auto bgFollower = new CameraFollower(bgObject);
	bgObject->AddComponent(bgFollower);
	bgSprite = new Sprite(bgObject);
	bgObject->AddComponent(bgSprite);
	AddObject(bgObject);

	// ----------------------------------- MENU ---------------------------------------------

	auto menuObj = new GameObject();
	auto menu = ActionMenu(menuObj);

	auto actionMenuObj = new GameObject();
	auto actionMenu = new ActionMenu(actionMenuObj);
	actionMenuObj->AddComponent(actionMenu);
	this->AddObject(actionMenuObj);

	auto actionMenuSelectorObj = new GameObject();
	auto actionMenuSelector = new ActionMenuSelector(actionMenuSelectorObj, nullptr);
	actionMenuSelectorObj->AddComponent(actionMenuSelector);
	this->AddObject(actionMenuSelectorObj);

	auto attackButtonObj = new GameObject();
	auto attackButton = new AttackButton(attackButtonObj, actionMenu);
	attackButtonObj->AddComponent(attackButton);
	this->AddObject(attackButtonObj);

	auto defendButtonObj = new GameObject();
	auto defendButton = new DefendButton(defendButtonObj, actionMenu);
	defendButtonObj->AddComponent(defendButton);
	this->AddObject(defendButtonObj);

	auto skillButtonObj = new GameObject();
	auto skillButton = new SkillButton(skillButtonObj, actionMenu);
	skillButtonObj->AddComponent(skillButton);
	this->AddObject(skillButtonObj);

	actionMenu->setButtons({attackButton, defendButton, skillButton});
	actionMenu->setSelector(actionMenuSelector);
	actionMenuSelector->setAttached(attackButton);
	// ----------------------------------- MENU ---------------------------------------------

	// //------------------------------------- MUSHROOM -----------------------------------------------------

	// auto mushroomObj = new GameObject();
	// mushroomObj->setScale(Vec2(5, 5));

	// auto mushroomSprite = Mushroom::CreateIdleSprite(mushroomObj);
	// // mushroomObj->AddComponent(mushroomSprite);
	// auto mushroom = new Mushroom(mushroomObj, 100, 100, 100, 100, 5, 10, 5, 1, 50, mushroomSprite);
	// mushroomObj->AddComponent(mushroom);
	// this->AddObject(mushroomObj);

	// auto mushroomHealthBarObj = new GameObject();
	// auto mushroomHealthBar = new HealthBar(mushroomHealthBarObj, mushroom);
	// mushroomHealthBarObj->AddComponent(mushroomHealthBar);
	// this->AddObject(mushroomHealthBarObj);

	// auto mushroomManaBarObj = new GameObject();
	// auto mushroomManaBar = new ManaBar(mushroomManaBarObj, mushroom);
	// mushroomManaBarObj->AddComponent(mushroomManaBar);
	// this->AddObject(mushroomManaBarObj);
	// //------------------------------------- MUSHROOM -----------------------------------------------------

	//------------------------------------- PORCO -----------------------------------------------------

	auto porcoObj = new GameObject();
	porcoObj->setScale(Vec2(3,3));

	auto porcoSprite = Porco::CreateIdleSprite(porcoObj);
	// porcoObj->AddComponent(porcoSprite);
	auto porco = new Porco(porcoObj, 100, 100, 100, 100, 5, 10, 5, 1, 50, porcoSprite);
	porcoObj->AddComponent(porco);
	this->AddObject(porcoObj);

	auto porcoHealthBarObj = new GameObject();
	auto porcoHealthBar = new HealthBar(porcoHealthBarObj, porco);
	porcoHealthBarObj->AddComponent(porcoHealthBar);
	this->AddObject(porcoHealthBarObj);

	auto porcoManaBarObj = new GameObject();
	auto porcoManaBar = new ManaBar(porcoManaBarObj, porco);
	porcoManaBarObj->AddComponent(porcoManaBar);
	this->AddObject(porcoManaBarObj);
	//------------------------------------- PORCO -----------------------------------------------------

	//------------------------------------- WARRIOR -----------------------------------------------------

	auto warriorObj = new GameObject();
	warriorObj->setScale(Vec2(3, 3));

	auto warriorIdleSprite = Warrior::CreateIdleSprite(warriorObj);

	auto warrior = new Warrior(warriorObj, 100, 100, 100, 100, 5, 1, 10, 10, 50, warriorIdleSprite);
	warriorObj->AddComponent(warrior);
	this->AddObject(warriorObj);

	auto warriorHealthBarObj = new GameObject();
	auto warriorHealthBar = new HealthBar(warriorHealthBarObj, warrior);
	warriorHealthBarObj->AddComponent(warriorHealthBar);
	this->AddObject(warriorHealthBarObj);

	auto warriorManaBarObj = new GameObject();
	auto warriorManaBar = new ManaBar(warriorManaBarObj, warrior);
	warriorManaBarObj->AddComponent(warriorManaBar);
	this->AddObject(warriorManaBarObj);

	characters.push_back(warrior);
	//------------------------------------- WARRIOR -----------------------------------------------------

	//------------------------------------- Bargudin -----------------------------------------------------

	auto bargudinObj = new GameObject();
	bargudinObj->setScale(Vec2(3, 3));

	auto bargudinIdleSprite = Bargudin::CreateIdleSprite(bargudinObj);

	auto bargudin = new Bargudin(bargudinObj, 100, 100, 100, 100, 5, 1, 10, 10, 50, bargudinIdleSprite);
	bargudinObj->AddComponent(bargudin);
	this->AddObject(bargudinObj);

	auto bargudinHealthBarObj = new GameObject();
	auto bargudinHealthBar = new HealthBar(bargudinHealthBarObj, bargudin);
	bargudinHealthBarObj->AddComponent(bargudinHealthBar);
	this->AddObject(bargudinHealthBarObj);

	auto bargudinManaBarObj = new GameObject();
	auto bargudinManaBar = new ManaBar(bargudinManaBarObj, bargudin);
	bargudinManaBarObj->AddComponent(bargudinManaBar);
	this->AddObject(bargudinManaBarObj);

	characters.push_back(bargudin);
	//------------------------------------- Bargudin -----------------------------------------------------

	auto indicatorObj = new GameObject();
	auto indicator = new CharacterIndicator(indicatorObj, warrior);
	indicatorObj->AddComponent(indicator);
	this->AddObject(indicatorObj);
	this->indicator = indicator;

	currentRound = Round::PlayerCharacterSelect;
}

void BattleState::LoadAssets()
{
	if (bgSprite)
	{
		bgSprite->Open("assets/img/battle.png");
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

	if (getRound() == Round::GameEnding)
	{

		this->popRequested = true;

		return;
	}

	if (this->getRound() == Round::PlayerAction)
	{
		if (selectedCharacter->isIdle)
		{
			auto selectedActionObj = this->getFirstObjectByComponent("ActionMenu");
			auto selectedActionMenu = (ActionMenu *)selectedActionObj->GetComponent("ActionMenu");
			auto selectedButton = selectedActionMenu->selector->getAttached();
			if (selectedButton->getType() == "AttackButton")
			{
				auto mushroom = this->getFirstObjectByComponent("Porco");
				auto mushroomPtr = (Porco *)mushroom->GetComponent("Porco");
				selectedCharacter->physicalAttack(mushroomPtr);
			}
			else if (selectedButton->getType() == "DefendButton")
			{
				selectedCharacter->defend();
				this->setRound(Round::EnemyActionSelect);
			}
			else if (selectedButton->getType() == "SkillButton")
			{
				auto mushroom = this->getFirstObjectByComponent("Porco");
				auto mushroomPtr = (Porco *)mushroom->GetComponent("Porco");
				selectedCharacter->useSkill(mushroomPtr);
			}
		}
	}

	if (getRound() == Round::PlayerRhythm)
	{
		if (balls.size() == 0)
		{

			const int maxNumCircles = 10;
			const int circleRadius = 200;

			std::random_device os_seed;
			const uint_least32_t seed = os_seed();
			std::mt19937 generator(seed);

			std::uniform_int_distribution<uint_least32_t> distributeY(circleRadius, SCREEN_HEIGHT - circleRadius);
			std::uniform_int_distribution<uint_least32_t> distributeX(circleRadius, SCREEN_WIDTH - circleRadius);

			for (size_t i = 0; i < maxNumCircles; i++)
			{
				auto newPosition = Vec2(distributeX(generator), distributeY(generator));
				auto ballObj = new GameObject();
				auto ballPtr = new ClickBall(ballObj, newPosition, 3, circleRadius);
				ballObj->AddComponent(ballPtr);
				balls.push_back(ballObj);
			}
		}

		else
		{
			auto currentBallObj = balls.front();
			auto currentBall = (ClickBall *)currentBallObj->GetComponent("ClickBall");
			balls.pop_front();

			if (currentBall->getRemainingTime() <= 0)
			{
				//  a bola que está na tela morreu sem ninguem clicar nela
				currentBallObj->RequestDelete();
				balls.clear();
				auto mushroom = this->getFirstObjectByComponent("Porco");
				auto mushroomPtr = (Porco *)mushroom->GetComponent("Porco");
				setRound(Round::PlayerAction);
				selectedCharacter->rhythmAttackEnd(mushroomPtr);
				return;
			}
			else if (currentBall->getHasRun() == false)
			{
				// Não tem nenhuma bola na tela
				this->AddObject(currentBallObj);
			}
			else
			{
				// Tem uma bola na tela e ela ainda não morreu
				if (InputManager::GetInstance().MousePress(SDL_BUTTON_LEFT))
				{
					if (currentBall->isPointInsideCircle(Vec2(mouseX, mouseY)))
					{
						auto mushroom = this->getFirstObjectByComponent("Porco");
						auto mushroomPtr = (Porco *)mushroom->GetComponent("Porco");
						selectedCharacter->rhythmAttack(mushroomPtr);
						currentBallObj->RequestDelete();
						if (balls.size() == 0)
						{
							selectedCharacter->rhythmAttackEnd(mushroomPtr);

							setRound(Round::PlayerAction);
						}
						return;
					}
					else
					{
						currentBallObj->RequestDelete();
						balls.clear();
						auto mushroom = this->getFirstObjectByComponent("Porco");
						auto mushroomPtr = (Porco *)mushroom->GetComponent("Porco");
						setRound(Round::PlayerAction);
						selectedCharacter->rhythmAttackEnd(mushroomPtr);
						return;
					}
				}
			}
			balls.push_front(currentBallObj);
		}
	}
	else if (getRound() == Round::EnemyAction || getRound() == Round::EnemyActionSelect)
	{
		auto mushroom = this->getFirstObjectByComponent("Porco");
		auto mushroomPtr = (Porco *)mushroom->GetComponent("Porco");
		if (mushroomPtr->isIdle == true)
		{
			mushroomPtr->physicalAttack(selectedCharacter);
		}
	}
	else if (getRound() == Round::PlayerCharacterSelectInit)
	{
		auto actionMenuObj = this->getFirstObjectByComponent("ActionMenu");
		auto actionMenuPtr = (ActionMenu *)actionMenuObj->GetComponent("ActionMenu");
		actionMenuPtr->setIsVisible(false);
		actionMenuPtr->selector->setAttached(actionMenuPtr->buttons[0]);
		this->selectedCharacter = nullptr;
		actionMenuPtr->selector->setIsActionLocked(false);
		indicator->setIsCharacterLocked(false);
		setRound(Round::PlayerCharacterSelect);
	}

	else if (getRound() == Round::PlayerCharacterSelect)
	{
		auto actionMenuObj = this->getFirstObjectByComponent("ActionMenu");
		auto actionMenuPtr = (ActionMenu *)actionMenuObj->GetComponent("ActionMenu");
		actionMenuPtr->setIsVisible(false);
		actionMenuPtr->selector->setIsActionLocked(false);

		if (InputManager::GetInstance().KeyPress(UP_ARROW_KEY))
		{
			if (indicator->getIsCharacterLocked() == false)
			{
				auto characterHealthBar = getFirstHealthBarOfEntityType(characters[indicatedCharacterIndex]->getType());
				if (characterHealthBar)
				{
					characterHealthBar->setIsVisible(false);
				}

				auto characterManaBar = getFirstManaBarOfEntityType(characters[indicatedCharacterIndex]->getType());
				if (characterManaBar)
				{
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
				if (characterHealthBar)
				{
					characterHealthBar->setIsVisible(false);
				}

				auto characterManaBar = getFirstManaBarOfEntityType(characters[indicatedCharacterIndex]->getType());
				if (characterManaBar)
				{
					characterManaBar->setIsVisible(false);
				}

				indicatedCharacterIndex = std::min(indicatedCharacterIndex + 1, (int)characters.size() - 1);
				indicator->setAttached(characters[indicatedCharacterIndex]);
			}
		}
		if (InputManager::GetInstance().KeyPress(SDLK_RETURN))
		{
			indicatedCharacterIndex = std::max(indicatedCharacterIndex, 0);
			indicator->setAttached(characters[indicatedCharacterIndex]);
			this->selectedCharacter = characters[indicatedCharacterIndex];
			indicator->setIsCharacterLocked(true);

			setRound(Round::PlayerActionSelect);
		}

		if (InputManager::GetInstance().KeyPress(SDLK_F1))
		{

			auto mushroomHealthBar = getFirstHealthBarOfEntityType("Porco");

			if (mushroomHealthBar)
				mushroomHealthBar->toggleVisibility();

			auto mushroomManaBar = getFirstManaBarOfEntityType("Porco");

			if (mushroomManaBar)
				mushroomManaBar->toggleVisibility();
		}

		if (InputManager::GetInstance().KeyPress(SDLK_KP_1))
		{
			auto mushroom = this->getFirstObjectByComponent("Porco");
			if (mushroom)
			{
				auto mushroomPtr = (Porco *)mushroom->GetComponent("Porco");
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

		if (InputManager::GetInstance().KeyPress(SDLK_KP_3))
		{
			auto mushroom = this->getFirstObjectByComponent("Porco");
			if (mushroom)
			{
				auto mushroomPtr = (Porco *)mushroom->GetComponent("Porco");
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
	}
	else if (getRound() == Round::PlayerActionSelect)
	{
		if (InputManager::GetInstance().KeyPress(SDLK_BACKSPACE))
		{
			auto selectedActionObj = this->getFirstObjectByComponent("ActionMenu");
			auto selectedActionMenu = (ActionMenu *)selectedActionObj->GetComponent("ActionMenu");
			if (selectedActionMenu->selector->getIsActionLocked() == false)
			{
				this->selectedCharacter = nullptr;
				indicator->setIsCharacterLocked(false);
				setRound(Round::PlayerCharacterSelectInit);
			}
		}

		if (InputManager::GetInstance().MousePress(SDL_BUTTON_LEFT))
		{
			auto attackButtonobj = this->getFirstObjectByComponent("AttackButton");
			if (attackButtonobj->getBox().Contains({mouseX, mouseY}))
			{
				auto mushroomObj = this->getFirstObjectByComponent("Porco");
				auto warriorObj = this->getFirstObjectByComponent("Warrior");
				auto mushroomPtr = (Porco *)mushroomObj->GetComponent("Porco");
				auto warriorPtr = (Warrior *)warriorObj->GetComponent("Warrior");
				mushroomPtr->gainHp(100);
				warriorPtr->gainHp(100);
			}

			auto defendButtonObj = this->getFirstObjectByComponent("DefendButton");
			if (defendButtonObj->getBox().Contains({mouseX, mouseY}))
			{
				auto mushroomObj = this->getFirstObjectByComponent("Porco");
				auto warriorObj = this->getFirstObjectByComponent("Warrior");
				auto mushroomPtr = (Porco *)mushroomObj->GetComponent("Porco");
				auto warriorPtr = (Warrior *)warriorObj->GetComponent("Warrior");
				mushroomPtr->gainMp(100);
				warriorPtr->gainMp(100);
			}
		}
	}
	else
	{
	}

	UpdateArray(dt);

	// for (size_t i = 0; i < this->objectArray.size(); i++)
	// {
	// 	if (auto colliderPtr = (Collider *)objectArray[i]->GetComponent("Collider"))
	// 	{
	// 		colliders.push_back({objectArray[i], colliderPtr});
	// 	}
	// }

	// for (size_t i = 0; i < colliders.size(); i++)
	// {
	// 	for (size_t j = i + 1; j < colliders.size(); j++)
	// 	{
	// 		if (Collider::IsColliding(colliders[i].second->box, colliders[j].second->box, colliders[i].first->angleDeg, colliders[j].first->angleDeg))
	// 		{
	// 			colliders[i].first->NotifyCollision(*colliders[j].first);
	// 			colliders[j].first->NotifyCollision(*colliders[i].first);
	// 		}
	// 	}
	// }

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

void BattleState::setRound(Round turn)
{
	this->currentRound = turn;
}

BattleState::Round BattleState::getRound()
{
	return currentRound;
}

#include "Penguin/StageState.hpp"
#include "Vec2.hpp"
#include "Sound.hpp"
#include <memory>
#include "my_utility.hpp"
#include "Penguin/TileMap.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "CameraFollower.hpp"
#include "Penguin/Alien.hpp"
#include "Penguin/PenguinBody.hpp"
#include "Collider.hpp"
#include "Game.hpp"
#include "CameraFollower.hpp"
#include "GameData.hpp"
#include "EndState.hpp"
#include <random>

StageState::StageState()
{
	this->quitRequested = false;
	this->started = false;

	this->backgroundMusic = Music();

	auto mapObject = new GameObject();

	auto bgObject = new GameObject();
	auto bgFollower = new CameraFollower(*bgObject);
	bgObject->AddComponent(bgFollower);
	bgSprite = new Sprite(*bgObject);
	bgObject->AddComponent(bgSprite);
	AddObject(bgObject);

	auto tileset = new TileSet(64, 64, "assets/img/Penguin/tileset.png");
	mapObject->AddComponent(new TileMap(*mapObject, "assets/map/tileMap.txt", tileset));
	this->AddObject(mapObject);

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> distAlien(2, 6);
	std::uniform_int_distribution<std::mt19937::result_type> distMinions(2, 7);
	std::uniform_int_distribution<std::mt19937::result_type> distXAlien(1, SCREEN_WIDTH);
	std::uniform_int_distribution<std::mt19937::result_type> distYAlien(1, SCREEN_HEIGHT);

	auto nAliens = distAlien(rng);
	for (size_t i = 0; i < nAliens; i++)
	{
		auto alienObject = new GameObject();
		auto alien = new Alien(*alienObject, distMinions(rng));
		alienObject->setBoxCenter(Vec2(distXAlien(rng), distYAlien(rng)));
		alienObject->AddComponent(alien);

		this->AddObject(alienObject);
		this->aliens.push_back(alienObject);
	}

	auto bodyObject = new GameObject();
	auto body = new PenguinBody(*bodyObject);
	bodyObject->AddComponent(body);

	bodyObject->setBoxCenter(Vec2(704, 640));
	Camera::Follow(bodyObject);

	this->AddObject(bodyObject);
}

StageState::~StageState()
{
}

void StageState::LoadAssets()
{
	if (bgSprite)
	{
		bgSprite->Open("assets/img/Penguin/ocean.jpg");
	}

	this->backgroundMusic.Open("assets/audio/stageState.ogg");
	this->backgroundMusic.Play();
}

void StageState::Start()
{
	started = true;
	this->LoadAssets();

	StartArray();
}

void StageState::Update(float dt)
{

	// camera update
	Camera::Update(dt);

	std::vector<std::pair<std::shared_ptr<GameObject>, Collider *>> colliders;

	if (InputManager::GetInstance().QuitRequested() || InputManager::GetInstance().KeyPress(ESCAPE_KEY))
	{
		this->quitRequested = true;
	}
	auto playerPtr = PenguinBody::player;
	if (!playerPtr)
	{
		// Player died
		GameData::playerVictory = false;
		popRequested = true;
		Game::GetInstance().Push(new EndState());
		return;
	}

	// Ver qual alien morreu
	for (size_t i = 0; i < aliens.size(); i++)

	{
		if (aliens[i]->IsDead())
		{
			aliens.erase(aliens.begin() + i);
		}
	}
	// Caso os aliens acabem:
	bool hasEnemies = aliens.size() > 0;

	if (!hasEnemies)
	{
		GameData::playerVictory = true;
		popRequested = true;
		Game::GetInstance().Push(new EndState());
		return;
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

void StageState::Render()
{
	this->RenderArray();
}

void StageState::Pause()
{
}

void StageState::Resume()
{
}
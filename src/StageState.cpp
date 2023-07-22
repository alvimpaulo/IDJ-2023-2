
#include "StageState.hpp"
#include "Vec2.hpp"
#include "Sound.hpp"
#include <memory>
#include "my_utility.hpp"
#include "TileMap.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "CameraFollower.hpp"
#include "Alien.hpp"
#include "PenguinBody.hpp"
#include "Collider.hpp"
#include "Game.hpp"

StageState::StageState()
{
	this->quitRequested = false;
	this->started = false;

	this->backgroundMusic = Music();

	auto mapObject = new GameObject();

	auto tileset = new TileSet(64, 64, "assets/img/tileset.png");
	mapObject->AddComponent(new TileMap(*mapObject, "assets/map/tileMap.txt", tileset));
	this->AddObject(mapObject);

	auto alienObject = new GameObject();
	auto alien = new Alien(*alienObject, 5);
	alienObject->box.SetCenter(Vec2(512, 300));
	alienObject->AddComponent(alien);

	this->AddObject(alienObject);

	auto bodyObject = new GameObject();
	auto body = new PenguinBody(*bodyObject);
	bodyObject->AddComponent(body);

	bodyObject->box.SetCenter(Vec2(704, 640));
	Camera::Follow(bodyObject);

	this->AddObject(bodyObject);
}

StageState::~StageState()
{
}

void StageState::LoadAssets()
{
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

	if (InputManager::GetInstance().QuitRequested())
	{
		this->quitRequested = true;
	}

	if(InputManager::GetInstance().KeyPress(ESCAPE_KEY)){
		this->popRequested = true;
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

void StageState::Pause(){

}

void StageState::Resume(){

}
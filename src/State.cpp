
#include "State.hpp"
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

State::State()
{
	this->quitRequested = false;
	this->started = false;

	this->music = Music();

	auto bgObject = std::make_shared<GameObject>();
	auto bgFollower = new CameraFollower(*bgObject);
	auto bgSprite = new Sprite(*bgObject);

	bgObject->AddComponent(bgFollower);
	bgObject->AddComponent(bgSprite);

	this->AddObject(bgObject);

	this->bg = std::unique_ptr<Sprite>(bgSprite);

	auto mapObject = std::make_shared<GameObject>();

	auto tileset = new TileSet(64, 64, "assets/img/tileset.png");
	mapObject->AddComponent(new TileMap(*mapObject, "assets/map/tileMap.txt", tileset));
	this->AddObject(mapObject);

	auto alienObject = std::make_shared<GameObject>();
	auto alien = new Alien(*alienObject, 5);
	alienObject->box.SetCenter(Vec2(512, 300));
	alienObject->AddComponent(alien);

	this->AddObject(alienObject);

	auto bodyObject = std::make_shared<GameObject>();
	auto body = new PenguinBody(*bodyObject);
	bodyObject->AddComponent(body);

	bodyObject->box.SetCenter(Vec2(704, 640));
	Camera::Follow(bodyObject.get());

	this->AddObject(bodyObject);
}

State::~State()
{
}

void State::LoadAssets()
{
	this->music.Open("assets/audio/stageState.ogg");
	this->music.Play();
	this->bg->Open("assets/img/ocean.jpg");
}

void State::Start()
{
	this->LoadAssets();

	for (size_t i = 0; i < objectArray.size(); i++)
	{
		objectArray[i]->Start();
	}

	started = true;
}

void State::Update(float dt)
{

	// camera update
	Camera::Update(dt);

	std::vector<std::pair<std::shared_ptr<GameObject>, Collider *>> colliders;

	if (InputManager::GetInstance().QuitRequested() || InputManager::GetInstance().KeyPress(SDLK_ESCAPE))
	{
		this->quitRequested = true;
	}

	if (InputManager::GetInstance().KeyPress(SDLK_SPACE))
	{
	}

	for (size_t i = 0; i < this->objectArray.size(); i++)
	{
		objectArray[i]->Update(dt);
	}

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

void State::Render()
{
	this->bg->Render();

	for (auto &it : objectArray)
	{
		it->Render();
	}
}

bool State::QuitRequested()
{
	return quitRequested;
}

std::weak_ptr<GameObject> State::AddObject(std::shared_ptr<GameObject> go)
{

	objectArray.emplace_back(go);

	if (started)
	{
		go->Start();
	}

	return std::weak_ptr<GameObject>(go);
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject *go)
{
	for (auto &it : objectArray)
	{
		if ((it).get() == go)
		{
			return std::weak_ptr<GameObject>(it);
		}
	}

	return std::weak_ptr<GameObject>();
}
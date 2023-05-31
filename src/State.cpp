
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

#define PI 3.14159265358979323846

State::State()
{
	this->quitRequested = false;
	this->started = false;

	this->music = Music();

	auto bgObject = new GameObject();
	auto bgFollower = new CameraFollower(*bgObject);
	auto bgSprite = new Sprite(*bgObject);

	bgObject->AddComponent(bgFollower);
	bgObject->AddComponent(bgSprite);

	this->AddObject(bgObject);

	this->bg = std::unique_ptr<Sprite>(bgSprite);

	auto mapObject = new GameObject();

	auto tileset = new TileSet(64, 64, "assets/img/tileset.png");
	mapObject->AddComponent(new TileMap(*mapObject, "assets/map/tileMap.txt", tileset));
	this->AddObject(mapObject);

	auto alienObject = new GameObject();
	auto alien = new Alien(*alienObject, 2);
	alienObject->box.SetCenter(Vec2(512, 300));
	alienObject->AddComponent(alien);

	this->AddObject(alienObject);
}

State::~State()
{

	this->objectArray.clear();
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

	for (auto &it : objectArray)
	{
		it->Start();
	}

	started = true;
}

void State::Update(float dt)
{

	// camera update
	Camera::Update(dt);

	if (InputManager::GetInstance().QuitRequested() || InputManager::GetInstance().KeyPress(SDLK_ESCAPE))
	{
		this->quitRequested = true;
	}

	if (InputManager::GetInstance().KeyPress(SDLK_SPACE))
	{
	}

	for (auto &it : this->objectArray)
	{
		it->Update(dt);
	}

	for (size_t i = 0; i < this->objectArray.size(); i++)
	{
		if (objectArray[i]->IsDead())
		{
			if (objectArray[i]->IsEmpty())
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

std::weak_ptr<GameObject> State::AddObject(GameObject *go)
{
	if (started)
	{
		go->Start();
	}

	auto ptr = std::shared_ptr<GameObject>(go);

	objectArray.emplace_back(ptr);

	return std::weak_ptr<GameObject>(ptr);
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

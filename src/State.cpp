
#include "State.hpp"
#include "Face.hpp"
#include "Vec2.hpp"
#include "Sound.hpp"
#include <memory>
#include "my_utility.hpp"
#include "TileMap.hpp"
#include "InputManager.hpp"

#define PI 3.14159265358979323846

State::State()
{
	this->quitRequested = false;

	this->music = Music();

	auto mapObject = new GameObject();
	mapObject->box.x = 0;
	mapObject->box.y = 0;
	auto tileset = new TileSet(64, 64, "assets/img/tileset.png");

	mapObject->AddComponent(new TileMap(*mapObject, "assets/map/tileMap.txt", tileset));

	this->objectArray.emplace_back(mapObject);

	this->bg = std::unique_ptr<Sprite>(new Sprite(*mapObject));
}

State::~State()
{

	this->objectArray.clear();
}

void State::LoadAssets()
{
	this->music.Open("assets/audio/stageState.ogg");
	this->music.Play();
	// this->bg->Open("assets/img/ocean.jpg");
}

void State::Update(float dt)
{
	if (InputManager::GetInstance().QuitRequested() || InputManager::GetInstance().KeyPress(SDLK_ESCAPE))
	{
		this->quitRequested = true;
	}

	if (InputManager::GetInstance().KeyPress(SDLK_SPACE))
	{
		Vec2 objPos = Vec2(200, 0).getRotated(static_cast<float>(-PI + PI * (rand() % 1001) / static_cast<float>(500.0))) + Vec2((InputManager::GetInstance().GetMouseX()), (InputManager::GetInstance().GetMouseY()));
		AddObject((int)objPos.x, (int)objPos.y);
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

void State::AddObject(int mouseX, int mouseY)
{
	auto newObject = new GameObject();

	auto faceSprite = new Sprite(*newObject, "assets/img/penguinface.png");
	newObject->box.x = static_cast<float>(mouseX) + (static_cast<float>(faceSprite->GetWidth()) / 2);
	newObject->box.y = static_cast<float>(mouseY) + (static_cast<float>(faceSprite->getHeight()) / 2);
	newObject->AddComponent(faceSprite);

	newObject->AddComponent(new Sound(*newObject, "assets/audio/boom.wav"));

	auto face = new Face(*newObject);
	newObject->AddComponent(face);

	objectArray.emplace_back(newObject);
}


#include "State.hpp"
#include "Face.hpp"
#include "Vec2.hpp"
#include "Sound.hpp"
#include <memory>
#include "my_utility.hpp"

#define PI 3.14159265358979323846

State::State()
{
	this->quitRequested = false;

	this->music = Music();

	auto bgObject = new GameObject();
	this->bg = std::unique_ptr<Sprite>(new Sprite(*bgObject));
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

void State::Update(float dt)
{
	Input();
	for (auto &it : this->objectArray)
	{
		it->Update(dt);
	}

	for (size_t i = 0; i < this->objectArray.size(); i++)
	{
		if (objectArray[i]->IsDead())
		{
			if(objectArray[i]->IsEmpty())
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

void State::Input()
{
	SDL_Event event;
	int mouseX, mouseY;

	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
	while (SDL_PollEvent(&event))
	{

		// Se o evento for quit, setar a flag para terminação
		if (event.type == SDL_QUIT)
		{
			quitRequested = true;
		}

		// Se o evento for clique...
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{

			// Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
			for (int i = static_cast<int>(objectArray.size() - 1); i >= 0; --i)
			{
				// Obtem o ponteiro e casta pra Face.
				GameObject *go = (GameObject *)objectArray[i].get();
				// Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
				// O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
				// ao usar get(), violamos esse princípio e estamos menos seguros.
				// Esse código, assim como a classe Face, é provisório. Futuramente, para
				// chamar funções de GameObjects, use objectArray[i]->função() direto.

				if (go->box.Contains({(float)mouseX, (float)mouseY}))
				{
					auto faceCpt = go->GetComponent("Face");
					if (nullptr != faceCpt)
					{
						auto face = (Face *)(faceCpt);
						// Aplica dano
						face->Damage(std::rand() % 10 + 10);
						// Sai do loop (só queremos acertar um)
						break;
					}
				}
			}
		}
		if (event.type == SDL_KEYDOWN)
		{
			// Se a tecla for ESC, setar a flag de quit
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				quitRequested = true;
			}
			// Se não, crie um objeto
			else
			{
				Vec2 objPos = Vec2(200, 0).getRotated(static_cast<float>(-PI + PI * (rand() % 1001) / static_cast<float>(500.0))) + Vec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
				AddObject((int)objPos.x, (int)objPos.y);
			}
		}
	}
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

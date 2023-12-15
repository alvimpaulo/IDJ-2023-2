#include "InputManager.hpp"
#include <cstring>
#include <SDL2/SDL.h>
#include <limits.h>

InputManager::InputManager()
{
	memset(mouseState, 0, sizeof(mouseState));
	memset(mouseUpdate, 0, sizeof(mouseUpdate));

	quitRequested = false;

	updateCounter = 0;

	mouseX = 0;
	mouseY = 0;
}

InputManager::~InputManager() {}


void InputManager::Update()
{
	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	quitRequested = false;

	SDL_Event event;

	updateCounter = (updateCounter + 1) % INT_MAX;

	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
	while (SDL_PollEvent(&event))
	{
		// Se for repetido, não fazer nada
		if (event.key.repeat == 1)
		{
			continue;
		}
		// Se o evento for quit, setar a flag para terminação
		if (event.type == SDL_QUIT)
		{
			quitRequested = true;
			continue;
		}

		// Se o evento for clique...
		if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
		{
			int mouseButton = event.button.	button;
			mouseState[mouseButton] = (event.type == SDL_MOUSEBUTTONDOWN);
			mouseUpdate[mouseButton] = updateCounter;
		}

		if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
		{
			auto stateIterator = keyState.find(event.key.keysym.sym);

			if (stateIterator != keyState.end())
			{
				stateIterator->second = (event.type == SDL_KEYDOWN);
				keyUpdate.find(event.key.keysym.sym)->second = updateCounter;
			}
			else
			{
				keyState[event.key.keysym.sym] = (event.type == SDL_KEYDOWN);
				keyUpdate[event.key.keysym.sym] = updateCounter;
			}
		}
	}
}

bool InputManager::KeyPress(int key)
{
	auto isKey = keyState.find(key) != keyState.end();

	if (isKey && keyState.at(key) && keyUpdate.at(key) == updateCounter)
		return true;
	else
		return false;
}

bool InputManager::KeyRelease(int key)
{
	auto isKey = keyState.find(key) != keyState.end();
	if (isKey && !keyState.at(key) && keyUpdate.at(key) == updateCounter)
		return true;
	else
		return false;
}

bool InputManager::AnyKeyPress()
{
    for(auto &it: keyState){
		if(it.second){
			return true;
		}
	}
	return false;
}

bool InputManager::IsKeyDown(int key)
{
	auto isKey = keyState.find(key) != keyState.end();
	if (isKey && keyState.at(key))
		return true;
	else
		return false;
}

bool InputManager::MousePress(int key)
{
	if (mouseState[key] && mouseUpdate[key] == updateCounter)
		return true;
	else
		return false;
}

bool InputManager::MouseRelease(int key)
{
	if (!mouseState[key] && mouseUpdate[key] == updateCounter)
		return true;
	else
		return false;
}

bool InputManager::IsMouseDown(int key)
{
	if (mouseState[key])
		return true;
	else
		return false;
}

int InputManager::GetMouseX()
{
	return mouseX;
}

int InputManager::GetMouseY()
{
	return mouseY;
}

bool InputManager::QuitRequested()
{
	return quitRequested;
}

InputManager &InputManager::GetInstance()
{
	static InputManager I;
	return I;
}
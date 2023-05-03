#include "Sound.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include "Face.hpp"

Sound::Sound(GameObject &associated) : Component(associated)
{
}
Sound::Sound(GameObject &associated,
             std::string file) : Sound(associated)
{
    Open(file);
}
Sound::~Sound()
{
    if (chunk != nullptr)
    {
        int haltResult = 0;
        if (channel > 0)
            haltResult = Mix_HaltChannel(channel);
        if (haltResult != 0)
        {
            std::cerr << "Erro no halt dentro do destrutor de sound" << std::endl;
            exit(0);
        }
        Mix_FreeChunk(chunk);
    }
}
void Sound::Play(int times)
{
    int newChannel = -1;
    newChannel = Mix_PlayChannel(-1, chunk, times - 1);
    if (newChannel == -1)
    {
        std::cerr << "Erro tentando dar play" << std::endl;
        exit(0);
    }
    this->channel = newChannel;
}
void Sound::Stop()
{
    if (chunk != nullptr)
    {
        int haltResult = 0;
        haltResult = Mix_HaltChannel(channel);
        if (haltResult != 0)
        {
            std::cerr << "Erro no halt dentro do Stop" << std::endl;
            exit(0);
        }
    }
}
void Sound::Open(std::string file)
{

    chunk = Mix_LoadWAV(file.c_str());

    if (chunk == nullptr)
    {
        std::cerr << "Erro tentando abrir o arquivo " << file << std::endl;
        exit(0);
    }
}
bool Sound::IsOpen()
{
    return chunk != nullptr;
}
void Sound::Update(float dt)
{
    if (associated.IsDead() && Mix_Playing(channel) == 0)
    {
        associated.RemoveComponent(associated.GetComponent("Sound"));
    }
}
void Sound::Render()
{
}
bool Sound::Is(std::string type)
{
    return type == "Sound";
}
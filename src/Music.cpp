#include "Music.hpp"
#include "Resources.hpp"

Music::Music()
{
    music = nullptr;
}

Music::Music(std::string file)
{
    Open(file);
}

void Music::Play(int times)
{

    if (music == nullptr)
    {
        std::cerr << "Tentou tocar uma musica a partir de um nullptr" << std::endl;
        exit(0);
    }

    int result = 0;
    result = Mix_PlayMusic(music, times);

    if (result != 0)
    {
        std::cerr << SDL_GetError() << std::endl;
    }
}

void Music::Stop(int msToStop)
{
    // int result = 0;
    Mix_FadeOutMusic(msToStop);
}

void Music::Open(std::string file)
{

    music = Resources::GetMusic(file);
}

bool Music::IsOpen()
{
    return music != nullptr;
}

Music::~Music()
{
}
#include "Resources.hpp"
#include "Game.hpp"

std::unordered_map<std::string, SDL_Texture *> Resources::imageTable;
std::unordered_map<std::string, Mix_Music *> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk *> Resources::soundTable;

SDL_Texture *Resources::GetImage(std::string file)
{
    auto imgLocation = Resources::imageTable.find(file);
    if (imgLocation != Resources::imageTable.end())
    {
        return (*imgLocation).second;
    }

    else
    {
        auto newTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());

        if (newTexture == NULL)
        {
            std::cerr << "Erro abrindo a textura " << file << std::endl;
            std::cerr << SDL_GetError() << std::endl;
            exit(0);
        }
        Resources::imageTable.emplace(file, newTexture);
        return newTexture;
    }
}

void Resources::ClearImages()
{
    for (auto &it : Resources::imageTable)
    {
        SDL_DestroyTexture(it.second);
    }
    imageTable.clear();
}

Mix_Music *Resources::GetMusic(std::string file)
{
    auto musicLocation = Resources::musicTable.find(file);
    if (musicLocation != Resources::musicTable.end())
    {
        return (*musicLocation).second;
    }

    else
    {
        auto newMusic = Mix_LoadMUS(file.c_str());

        if (newMusic == NULL)
        {
            std::cerr << "Erro abrindo a musica " << file << std::endl;
            std::cerr << SDL_GetError() << std::endl;
            exit(0);
        }
        Resources::musicTable.emplace(file, newMusic);
        return newMusic;
    }
}

void Resources::ClearMusics()
{
    for (auto &it : Resources::musicTable)
    {
        Mix_FreeMusic(it.second);
    }
    musicTable.clear();
}

Mix_Chunk *Resources::GetSound(std::string file)
{
    auto soundLocation = Resources::soundTable.find(file);
    if (soundLocation != Resources::soundTable.end())
    {
        return (*soundLocation).second;
    }

    else
    {
        auto newSound = Mix_LoadWAV(file.c_str());

        if (newSound == NULL)
        {
            std::cerr << "Erro abrindo o sound " << file << std::endl;
            std::cerr << SDL_GetError() << std::endl;
            exit(0);
        }
        Resources::soundTable.emplace(file, newSound);
        return newSound;
    }
}
void Resources::ClearSounds()
{
    for (auto &it : Resources::soundTable)
    {
        Mix_FreeChunk(it.second);
    }
    imageTable.clear();
}
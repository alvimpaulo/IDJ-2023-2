#include "Resources.hpp"
#include "Game.hpp"
#include <SDL_ttf.h>

std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> Resources::imageTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Music>> Resources::musicTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> Resources::soundTable;
std::unordered_map<std::string, std::shared_ptr<TTF_Font>> Resources::fontTable;

std::shared_ptr<SDL_Texture> Resources::GetImage(std::string file)
{
    auto imgLocation = Resources::imageTable.find(file);
    if (imgLocation != Resources::imageTable.end())
    {
        return (*imgLocation).second;
    }

    else
    {
        auto newTexture = std::shared_ptr<SDL_Texture>(IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str()), [](SDL_Texture *texture)
                                                       { SDL_DestroyTexture(texture); });

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
    for (auto it = imageTable.begin(); it != imageTable.end();)
    {
        if (it->second.unique())
        {
            imageTable.erase(it++);
        }
        else
        {
            it++;
        }
    }
}

std::shared_ptr<Mix_Music> Resources::GetMusic(std::string file)
{
    auto musicLocation = Resources::musicTable.find(file);
    if (musicLocation != Resources::musicTable.end())
    {
        return (*musicLocation).second;
    }

    else
    {
        auto newMusic = std::shared_ptr<Mix_Music>(Mix_LoadMUS(file.c_str()),
                                                   [](Mix_Music *music)
                                                   {
                                                       Mix_FreeMusic(music);
                                                   });

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
    for (auto it = musicTable.begin(); it != musicTable.end();)
    {
        if (it->second.unique())
        {
            musicTable.erase(it++);
        }
        else
        {
            it++;
        }
    }
}

std::shared_ptr<Mix_Chunk> Resources::GetSound(std::string file)
{
    auto soundLocation = Resources::soundTable.find(file);
    if (soundLocation != Resources::soundTable.end())
    {
        return (*soundLocation).second;
    }

    else
    {
        auto newSound = std::shared_ptr<Mix_Chunk>(Mix_LoadWAV(file.c_str()),
                                                   [](Mix_Chunk *sound)
                                                   {
                                                       Mix_FreeChunk(sound);
                                                   });

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
    for (auto it = soundTable.begin(); it != soundTable.end();)
    {
        if (it->second.unique())
        {
            it = soundTable.erase(it++);
        }
        else
        {
            it++;
        }
    }
}

std::shared_ptr<TTF_Font> Resources::GetFont(std::string file, int ptsize)
{

    auto it = fontTable.find(file + std::to_string(ptsize));
    if (it != fontTable.end())
        return it->second;

    auto newFont = std::shared_ptr<TTF_Font>(TTF_OpenFont(file.c_str(), ptsize),
                                             [](TTF_Font *font)
                                             {
                                                //  TTF_CloseFont(font); ta dando segfault
                                             });

    fontTable.emplace(file + std::to_string(ptsize), newFont);
    return newFont;
}
void Resources::ClearFont(std::string, int ptsize)
{
     for (auto it = fontTable.begin(); it != fontTable.end();)
    {
        if (it->second.unique())
        {
            it = fontTable.erase(it++);
        }
        else
        {
            it++;
        }
    }
}
#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <unordered_map>
#include <memory>
#include <SDL_ttf.h>

class Resources
{
private:
    static std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> imageTable;
    static std::unordered_map<std::string, std::shared_ptr<Mix_Music>> musicTable;
    static std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> soundTable;
    static std::unordered_map<std::string, std::shared_ptr<TTF_Font>> fontTable;

public:

    static Resources &GetInstance();
    static  std::shared_ptr<SDL_Texture> GetImage(std::string file);
    static void ClearImages();

    static  std::shared_ptr<Mix_Music> GetMusic(std::string file);
    static void ClearMusics();
    static std::shared_ptr<Mix_Chunk> GetSound(std::string file);
    static void ClearSounds();

    static std::shared_ptr<TTF_Font> GetFont(std::string file, int ptsize);
    static void ClearFont(std::string, int ptsize);
};

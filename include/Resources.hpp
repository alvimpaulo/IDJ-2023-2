
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <unordered_map>

class Resources
{
private:
    std::unordered_map<std::string, SDL_Texture *> imageTable;
    std::unordered_map<std::string, Mix_Music *> musicTable;
    std::unordered_map<std::string, Mix_Chunk *> soundTable;

public:
    SDL_Texture *GetImage(std::string file);
    void ClearImages();

    Mix_Music *GetMusic(std::string file);
    void ClearMusics();
    Mix_Chunk *GetSound(std::string file);
    void ClearSounds();

};

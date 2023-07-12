#include "Game.hpp"
#include "Resources.hpp"
#include "InputManager.hpp"

Game &Game::GetInstance()
{
    if (Game::instance == nullptr)
    {
        Game::instance = new Game("Paulo Alvim - 170153657", SCREEN_WIDTH, SCREEN_HEIGHT);
        return *Game::instance;
    }
    else
    {
        return *Game::instance;
    }
}

Game::Game(std::string title, int width, int height)
{
    if (Game::instance != nullptr)
    {
        std::cerr << "Game instanciando com instancia ja existindo" << std::endl;
        exit(0);
    }
    else
    {
        Game::instance = this;
    }

    // init sdl
    int sdlCode = 0;

    sdlCode = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
    if (sdlCode != 0)
    {
        std::cerr << "Sdl não incializado corretamente" << std::endl;
        std::cerr << SDL_GetError() << std::endl;
        exit(0);
    }

    // init image
    int imgCode = 0;
    imgCode = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);

    if (imgCode != (IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF))
    {
        std::cerr << "Imagem da Sdl não incializado corretamente" << std::endl;
        std::cerr << imgCode << std::endl;
        exit(0);
    }

    // Init sound
    int soundCode = 0;
    soundCode = (MIX_INIT_OGG);

    if (soundCode != MIX_INIT_OGG)
    {
        std::cerr << "Som da Sdl não incializado corretamente" << std::endl;
        std::cerr << soundCode << std::endl;
        exit(0);
    }

    // Init mixer
    int mixCode = 0;
    mixCode = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
    if (mixCode != 0)
    {
        std::cerr << "Mixer da Sdl não incializado corretamente" << std::endl;
        std::cerr << mixCode << std::endl;
        exit(0);
    }

    // Init window
    this->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (this->window == nullptr)
    {
        std::cerr << "Window da Sdl não incializado corretamente" << std::endl;
        exit(0);
    }

    // Init renderer
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
    if (this->renderer == nullptr)
    {
        std::cerr << "Renderer da Sdl não incializado corretamente" << std::endl;
        exit(0);
    }

    this->state = new State();

    // Init timing
    frameStart = SDL_GetTicks();
    this->dt = 0.0;
}

Game::~Game()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_CloseAudio();
    Mix_Quit();

    IMG_Quit();

    

    // delete this->state;

    SDL_Quit();
}

State &Game::GetState()
{
    return *state;
}

SDL_Renderer *Game::GetRenderer()
{
    return this->renderer;
}

void Game::Run()
{

    this->state->Start();
    while (state->QuitRequested() == false)
    {
        this->CalculateDeltaTime();
        InputManager::GetInstance().Update();

        state->Update(33);
        state->Render();

        SDL_RenderPresent(this->renderer);

        SDL_Delay(33);
    }

    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();
}

void Game::CalculateDeltaTime()
{
    int currentTicks = SDL_GetTicks();
    auto deltaTicks = static_cast<float>(currentTicks) - this->dt;

    this->dt = deltaTicks / 1000;

    frameStart = currentTicks;
}

float Game::GetDeltaTime()
{
    return this->dt;
}
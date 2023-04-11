#include "Sprite.hpp"
#include "Game.hpp"

Sprite::Sprite()
{
    texture = nullptr;
}

Sprite::Sprite(std::string file)
{
    texture = nullptr;
    Open(file);
}

Sprite::~Sprite()
{
    if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
    }
}

void Sprite::Open(std::string file)
{
    if (this->texture != nullptr)
    {
        SDL_DestroyTexture(texture);
    }

    this->texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());

    if (this->texture == NULL)
    {
        std::cerr << "Erro abrindo a textura " << file << std::endl;
        std::cerr << SDL_GetError() << std::endl;
        exit(0);
    }

    SDL_QueryTexture(this->texture, nullptr, nullptr, &width, &height);

    std::cerr << "width: " << width << " Height: " << height << std::endl;

    SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h)
{
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render(int x, int y)
{
    SDL_Rect dstRect = SDL_Rect();
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = clipRect.w;
    dstRect.h = clipRect.h;

    int result = 0;
 
    result = SDL_RenderCopy(Game::GetInstance().GetRenderer(), this->texture, &clipRect, &dstRect);
    if (result != 0)
    {
        std::cerr << "Erro no SDL_RenderCopy " << result << std::endl;
        std::cerr << SDL_GetError() << std::endl;
        exit(0);
    }
}

int Sprite::getHeight()
{
    return this->height;
}

int Sprite::GetWidth()
{
    return this->width;
}

bool Sprite::IsOpen()
{
    return texture != nullptr;
}
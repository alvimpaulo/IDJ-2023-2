#include "Sprite.hpp"
#include "Game.hpp"
#include "GameObject.hpp"

Sprite::Sprite(GameObject &associated) : Component(associated)
{
    texture = nullptr;
}

Sprite::Sprite(GameObject &associated, std::string file) : Sprite(associated)
{
    Open(file);
}

Sprite::~Sprite()
{
    if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
    }
}

void Sprite::Update(float dt)
{
    if (associated.IsDead())
    {
        associated.RemoveComponent(this);
    }
}

bool Sprite::Is(std::string type)
{
    return type == "Sprite";
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

    // std::cerr << "width: " << width << " Height: " << height << std::endl;

    associated.box.x = 0;
    associated.box.y = 0;
    associated.box.w = width;
    associated.box.h = height;

    SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h)
{
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render(float x, float y, float w, float h){
    if(this->texture == NULL) return;

    SDL_Rect dstRect = SDL_Rect();
    dstRect.x = static_cast<int>(round(x));
    dstRect.y = static_cast<int>(round(y));
    dstRect.w = static_cast<int>(round(w));
    dstRect.h = static_cast<int>(round(h));

    int result = 0;

    result = SDL_RenderCopy(Game::GetInstance().GetRenderer(), this->texture, &clipRect, &dstRect);
    if (result != 0)
    {
        std::cerr << "Erro no SDL_RenderCopy " << result << std::endl;
        std::cerr << SDL_GetError() << std::endl;
        exit(0);
    }
}

void Sprite::Render()
{
    Render(associated.box.x, associated.box.y, associated.box.w, associated.box.h);
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
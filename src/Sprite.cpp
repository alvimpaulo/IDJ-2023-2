#include "Sprite.hpp"
#include "Game.hpp"
#include "GameObject.hpp"
#include "Resources.hpp"
#include "Camera.hpp"

Sprite::Sprite(GameObject &associated) : Component(associated)
{
    texture = nullptr;
    this->currentFrame = 0;
    this->frameCount = 1;
    this->frameTime = 1;
    this->timeElapsed = 0;
    this->secondsToSelfDestruct = 0;
    this->opacity = 255;
    this->flipHorizontal = false;
    this->flipVertical = false;
}

Sprite::Sprite(GameObject &associated, std::string file, int frameCount,
               float frameTime, float secondsToSelfDestruct, int opacity, bool flipHorizontal, bool flipVertical) : Component(associated)
{

    texture = nullptr;
    this->currentFrame = 0;
    this->frameCount = frameCount;
    this->frameTime = frameTime;
    this->timeElapsed = 0;
    this->secondsToSelfDestruct = secondsToSelfDestruct;
    this->opacity = opacity;
    this->flipHorizontal = flipHorizontal;
    this->flipVertical = flipVertical;

    Open(file);
}

Sprite::~Sprite()
{
}

void Sprite::Update(float dt)
{
    if (secondsToSelfDestruct > 0)
    {
        this->selfDesctructCount.Update(dt);
        if (selfDesctructCount.Get() > secondsToSelfDestruct)
        {
            associated.RequestDelete();
            return;
        }
    }

    timeElapsed += dt;
    if (frameTime < timeElapsed)
    {
        SetFrame((currentFrame + 1) % frameCount);
        timeElapsed = 0.0f;
    }

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

    this->texture = Resources::GetImage(file).get();
    SDL_SetTextureAlphaMod(this->texture, this->opacity);

    SDL_QueryTexture(this->texture, nullptr, nullptr, &width, &height);

    // std::cerr << "width: " << width << " Height: " << height << std::endl;

    associated.setBoxX(0);
    associated.setBoxY(0);

    width = width / frameCount;

    this->SetClip(0, 0, width, height);

    this->associated.setBoxW(float(width));
    this->associated.setBoxH(float(height));
}

void Sprite::SetClip(int x, int y, int w, int h)
{
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render(float x, float y, float w, float h)
{
    if (this->texture == NULL)
        return;

    auto boxCenter = associated.getBox().GetCenter();

    SDL_Rect dstRect = SDL_Rect();
    dstRect.x = (int)(round(x));
    dstRect.y = (int)(round(y));
    dstRect.w = (int)(round(w));
    dstRect.h = (int)(round(h));

    int result = 0;

    auto flips = SDL_FLIP_NONE;
    if (this->flipHorizontal)
        flips = SDL_FLIP_HORIZONTAL;
    if (this->flipVertical)
        flips = SDL_FLIP_VERTICAL;

    result = SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), this->texture, &clipRect, &dstRect, associated.angleDeg, nullptr, flips);
    if (result != 0)
    {
        std::cerr << "Erro no SDL_RenderCopy " << result << std::endl;
        std::cerr << SDL_GetError() << std::endl;
        exit(0);
    }
}

void Sprite::Render()
{

    float renderX = associated.getBox().x;
    float renderY = associated.getBox().y;

    Render(renderX, renderY, associated.getScaledBox().w, associated.getScaledBox().h);
}

bool Sprite::IsOpen()
{
    return texture != nullptr;
}

void Sprite::SetFrame(int frame)
{
    if (frame >= frameCount)
    {
        std::cerr << "SetFrame com numero maior que frameCount" << std::endl;
    }
    this->currentFrame = frame;

    auto framePosX = currentFrame * clipRect.w;
    auto framePosY = currentFrame * clipRect.y;

    SetClip(framePosX, framePosY, clipRect.w, clipRect.h);
}
void Sprite::SetFrameCount(int frameCount)
{
    this->frameCount = frameCount;
    SetFrame(0);

    this->associated.setBoxW(float(width));
    this->associated.setBoxH(float(height));
}
void Sprite::SetFrameTime(float frameTime)
{
    this->frameTime = frameTime;
}

void Sprite::setOpacity(int newOpacity)
{
    this->opacity = std::min(std::max(newOpacity, 0), 255);
}

int Sprite::getFrameCount()
{
    return frameCount;
}

int Sprite::getSingleFrameWidth()
{
    return associated.getBox().w / frameCount;
}
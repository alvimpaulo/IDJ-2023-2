#include "Text.hpp"
#include "Game.hpp"
#include "Camera.hpp"
#include "Resources.hpp"

Text::Text(GameObject *associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color) : Component(associated, "Text")
{
    this->fontFile = fontFile;
    this->fontSize = fontSize;
    this->style = style;
    this->text = text;
    this->color = color;

    font = Resources::GetFont(this->fontFile, this->fontSize).get();
    texture = nullptr;

    RemakeTexture();
}

Text::~Text()
{
    if (this->texture != nullptr)
    {
        SDL_DestroyTexture(texture);
    }
}

void Text::Update(float dt)
{
}

void Text::Render()
{
    auto dstPos = associated->getScaledBox();

    SDL_Rect clipRect{0, 0, (int)associated->getScaledBox().w, (int)associated->getScaledBox().h};
    SDL_Rect dstRect{(int)dstPos.x, (int)dstPos.y, (int)associated->getScaledBox().w, (int)associated->getScaledBox().h};

    int error = SDL_RenderCopyEx(Game::GetInstance().GetRenderer(),
                                 texture, &clipRect, &dstRect, associated->angleDeg, nullptr, SDL_FLIP_NONE);
    if (error)
    {
        std::cerr << "Erro renderizando Text " << SDL_GetError() << std::endl;
    }
}

void Text::SetText(std::string text)
{
    this->text = text;
    RemakeTexture();
}

void Text::SetStyle(TextStyle style)
{
    this->style = style;
    RemakeTexture();
}

void Text::SetFontFile(std::string fontFile)
{
    this->fontFile = fontFile;
    RemakeTexture();
}

void Text::SetFontSize(int fontSize)
{
    this->fontSize = fontSize;
    RemakeTexture();
}

void Text::RemakeTexture()
{
    if (this->texture)
    {
        SDL_DestroyTexture(texture);
    }

    SDL_Surface *surface = nullptr;
    SDL_Color bgColor = {0xff, 0xff, 0xff, 0xff};
    switch (style)
    {
    case SOLID:
        surface = TTF_RenderText_Solid(this->font, this->text.c_str(), this->color);
        break;
    case SHADED:
        surface = TTF_RenderText_Shaded(this->font, this->text.c_str(), this->color, bgColor);
        break;
    case BLENDED:
        surface = TTF_RenderText_Blended(this->font, this->text.c_str(), this->color);
        break;
    default:
        std::cerr << "Error: RemakeTexture sem style!" << std::endl;
        break;
    }

    texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);
    if (!texture)
    {
        std::cerr << "Error: Não criou a textura com SDL_CreateTextureFromSurface" << std::endl;
        return;
    }

    associated->setBoxW((float)surface->w);
    associated->setBoxH((float)surface->h);

    SDL_FreeSurface(surface);
}
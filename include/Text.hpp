#pragma once
#include "Component.hpp"
#include <SDL_ttf.h>

class Text : public Component
{
public:
    enum TextStyle
    {
        SOLID,
        SHADED,
        BLENDED
    };
    Text(GameObject *associated,
         std::string fontFile,
         int fontSize,
         TextStyle style,
         std::string text,
         SDL_Color color);

    ~Text();
    void Update(float dt);
    void Render();
    void SetText(std::string text);
    void SetColor(SDL_Color color);
    void SetStyle(TextStyle style);
    void SetFontFile(std::string fontFile);
    void SetFontSize(int fontSize);
    SDL_Color getColor();

private:
    void RemakeTexture();
    TTF_Font *font;
    SDL_Texture *texture;
    std::string text;
    TextStyle style;
    std::string fontFile;
    int fontSize;
    SDL_Color color;
};
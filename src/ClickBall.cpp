#include "ClickBall.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "Game.hpp"

// https://stackoverflow.com/questions/38334081/how-to-draw-circles-arcs-and-vector-graphics-in-sdl
// rounding helper, simplified version of the function I use
int roundUpToMultipleOfEight(int v)
{
    return (v + (8 - 1)) & -8;
}
void DrawCircle(SDL_Renderer *renderer, SDL_Point center, int radius)
{
    // 35 / 49 is a slightly biased approximation of 1/sqrt(2)
    const int arrSize = roundUpToMultipleOfEight(radius * 8 * 35 / 49);
    SDL_Point points[arrSize];
    int drawCount = 0;

    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        // Each of the following renders an octant of the circle
        points[drawCount + 0] = {center.x + x, center.y - y};
        points[drawCount + 1] = {center.x + x, center.y + y};
        points[drawCount + 2] = {center.x - x, center.y - y};
        points[drawCount + 3] = {center.x - x, center.y + y};
        points[drawCount + 4] = {center.x + y, center.y - x};
        points[drawCount + 5] = {center.x + y, center.y + x};
        points[drawCount + 6] = {center.x - y, center.y - x};
        points[drawCount + 7] = {center.x - y, center.y + x};

        drawCount += 8;

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }

    SDL_RenderDrawPoints(renderer, points, drawCount);
}

void DrawFilledCircle(SDL_Renderer *renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        //  Each of the following renders an octant of the circle
        SDL_RenderDrawLine(renderer, centreX + x, centreY - y, centreX + x, centreY + y);
        SDL_RenderDrawLine(renderer, centreX - x, centreY - y, centreX - x, centreY + y);
        SDL_RenderDrawLine(renderer, centreX + y, centreY - x, centreX + y, centreY + x);
        SDL_RenderDrawLine(renderer, centreX - y, centreY - x, centreX - y, centreY + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

ClickBall::ClickBall(GameObject *associated, Vec2 center, float durationInSeconds, int sizePixels) : Component(associated, "ClickBall")
{
    this->timeElapsed = 0.0;
    this->center = center;
    this->durationInSeconds = durationInSeconds;
    this->sizePixels = sizePixels;
}

void ClickBall::Update(float dt)
{
    timeElapsed += dt;
    //     if (timeElapsed >= durationInSeconds)
    //     {
    //         timeElapsed = 0;
    //     }
}

void ClickBall::Render()
{
    auto radius = this->getCurrentRadius();

    if (radius > 1)
    {
        auto renderer = Game::GetInstance().GetRenderer();
        SDL_SetRenderDrawColor(renderer, 255, 160, 0, 255);
        DrawFilledCircle(renderer, (int)center.x, (int)center.y, radius);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    }
}

float ClickBall::getRemainingTime()
{
    return this->durationInSeconds - this->timeElapsed;
}

bool ClickBall::getIsDead()
{
    return this->durationInSeconds - this->timeElapsed <= 0;
}

bool ClickBall::getHasRun()
{
    return this->timeElapsed != 0.0;
}

int ClickBall::getCurrentRadius()
{

    return ((timeElapsed) / this->durationInSeconds) * (this->sizePixels / 2);
}

bool ClickBall::isPointInsideCircle(Vec2 point)
{

    int dist = (point.x - this->center.x) * (point.x - this->center.x) + (point.y - center.y) * (point.y - center.y);
    if (dist <= getCurrentRadius() * getCurrentRadius())
        return true;
    else
        return false;
}

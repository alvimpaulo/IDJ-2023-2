#include "Timer.hpp"

Timer::Timer()
{
    this->time = 0;
}

void Timer::Update(float dt)
{
    time += dt;
}

void Timer::Restart()
{
    time = 0;
}

float Timer::Get()
{
    return time;
}
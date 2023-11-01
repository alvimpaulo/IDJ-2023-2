#pragma once
#include "Component.hpp"

class HealthBar : public Component
{
private:
    int maxHp;
    int currentHp;
    std::tuple<int, int, int> color;

public:
    HealthBar(GameObject &associated, int maxHp, int currentHp);
};
#include "Component.hpp"

class Minion : public Component
{
private:
    std::weak_ptr<GameObject> alienCenter;
    float arc;
public:
    Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg);
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void Shoot(Vec2 target);
};

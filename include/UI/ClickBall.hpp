#include "Component.hpp"

class ClickBall : public Component
{
private:
    Vec2 center;
    float timeElapsed;
    float durationInSeconds;
    int sizePixels;

public:
    bool isPointInsideCircle(Vec2 point);
    ClickBall(GameObject *associated, Vec2 center, float durationInSeconds, int sizePixels);
    void Update(float dt) override;
    void Render() override;
    float getRemainingTime();
    bool getIsDead();
    bool getHasRun();
    int getCurrentRadius();
};

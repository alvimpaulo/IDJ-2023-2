#include "Vec2.hpp"
#include "AnimationPhase.hpp"
#include <bits/stdc++.h>
#include "Component.hpp"
#include "Sprite.hpp"

class Animation : public Component
{
private:
    std::function<void()> startAnimationFunction;
    std::function<void()> endAnimationFunction;

public:
    Animation(int numFrames, Vec2 startPosition, Vec2 endPosition, Sprite *sprite, bool loop, std::function<void()> startAnimationFunction, std::function<void()> endAnimationFunction,
              AnimationPhase::Phase phase, GameObject *masterObject);
    int numFrames;
    Vec2 startPosition;
    Vec2 endPosition;
    int currentFrame;
    void Update(float dt) override;
    void Render() override;
    void StartAnimation();
    void EndAnimation();

    AnimationPhase::Phase phase;
    Sprite *sprite;
    bool loop;
    bool hasEnded;

    GameObject *masterObject;
};

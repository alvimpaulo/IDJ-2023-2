#include "Animation.hpp"

Animation::Animation(int numFrames, Vec2 startPosition, Vec2 endPosition, Sprite *sprite, bool loop, std::function<void()> startAnimation, std::function<void()> endAnimation, AnimationPhase::Phase phase, GameObject *masterObject) : Component(masterObject, "Animation")
{
    this->masterObject = masterObject;
    this->currentFrame = 0;
    this->numFrames = numFrames;
    this->endPosition = endPosition;
    this->startPosition = startPosition;

    this->sprite = sprite;
    this->loop = loop;

    this->phase = phase;
    this->endAnimationFunction = endAnimation;
    this->startAnimationFunction = startAnimation;
}

void Animation::Update(float dt)
{

    if (currentFrame > 0)
    {
        currentFrame++;
        if (sprite)
        {
            auto animationSpriteFrameRatio = (float)this->numFrames / sprite->getFrameCount();
            sprite->SetFrame(std::min(int(currentFrame / animationSpriteFrameRatio), sprite->getFrameCount() - 1));
        }

        if (phase == AnimationPhase::Phase::Idle)
        {
            if (currentFrame == numFrames)
            {
                this->EndAnimation();
            }
        }

        else
        {
            auto currentPosition = masterObject->getScaledBox().GetCenter();

            auto distanceX = endPosition.x - startPosition.x;
            auto distanceY = endPosition.y - startPosition.y;

            auto animationMoveDistanceX = distanceX / numFrames;
            auto animationMoveDistanceY = distanceY / numFrames;

            associated->setBoxCenter(Vec2(currentPosition.x + animationMoveDistanceX, currentPosition.y + animationMoveDistanceY));
        }

        if (currentFrame == numFrames)
        {
            EndAnimation();
        }
    }
}

void Animation::Render()
{
}

void Animation::StartAnimation()
{
    currentFrame = 1;
    if (startAnimationFunction)
        this->startAnimationFunction();
    if (sprite)
    {
        sprite->setCurrentFrame(0);
    }
}

void Animation::EndAnimation()
{
    if (endAnimationFunction)
        this->endAnimationFunction();
    if (loop)
    {
        StartAnimation();
    }
    else
    {
        currentFrame = 0;
    }
}

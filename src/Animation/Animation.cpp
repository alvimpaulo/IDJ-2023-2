#include "Animation.hpp"

Animation::Animation(int numFrames, Vec2 startPosition, Vec2 endPosition, Sprite *sprite, bool loop, std::function<void()> endAnimation, AnimationPhase::Phase phase, GameObject *masterObject) : Component(masterObject, "Animation")
{
    this->masterObject = masterObject;
    this->currentFrame = 0;
    this->numFrames = numFrames;
    this->endPosition = endPosition;
    this->startPosition = startPosition;

    this->sprite = sprite;
    this->loop = loop;

    this->phase = phase;
    this->endAnimation = endAnimation;
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
        }

        else
        {
            auto currentPosition = masterObject->getBox().GetCenter();

            auto distanceX = endPosition.x - startPosition.x;
            auto distanceY = endPosition.y - startPosition.y;

            auto animationMoveDistanceX = distanceX / numFrames;
            auto animationMoveDistanceY = distanceY / numFrames;

            associated->setBoxX(associated->getBox().x + animationMoveDistanceX);
            associated->setBoxY(associated->getBox().y + animationMoveDistanceY);
        }

        if (currentFrame == numFrames)
        {
            if (endAnimation)
                endAnimation();
            if (loop)
            {
                currentFrame = 1;
                if (sprite)
                {
                    sprite->setCurrentFrame(0);
                }
            }
            else
            {
                currentFrame = 0;
            }
        }
    }
}

void Animation::Render()
{
}

void Animation::startAnimation()
{
    currentFrame = 1;
}

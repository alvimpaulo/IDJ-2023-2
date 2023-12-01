#include "CameraFollower.hpp"
#include "Camera.hpp"

CameraFollower::CameraFollower(GameObject &go) : Component(go, "CameraFollower")
{
}

void CameraFollower::Update(float dt)
{
    this->associated.setBoxX(Camera::pos.x);
    this->associated.setBoxY(Camera::pos.y);
}

void CameraFollower::Render()
{
}
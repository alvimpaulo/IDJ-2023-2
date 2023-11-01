#include "GameObject.hpp"
#include <algorithm>
#include <memory>
#include "Component.hpp"
#include "Rect.hpp"
#include "Sprite.hpp"

GameObject::GameObject()
{
    this->isDead = false;
    this->started = false;
    this->angleDeg = 0;
    this->box = Rect();
    this->components = std::vector<std::unique_ptr<Component>>();
    this->scale = Vec2(1, 1);
}
GameObject::~GameObject()
{
    for (auto it = this->components.rbegin(); it != this->components.rend(); ++it)
    {
        components.erase(it.base()); // Talvez tenha que mudar para std::next(it).base()
    }

    components.clear();
}

void GameObject::Start()
{
    for (auto &it : this->components)
    {
        it->Start();
    }

    this->started = true;
}

void GameObject::Update(float dt)
{
    for (auto &it : components)
        if (it != nullptr)
            it->Update(dt);
}
void GameObject::Render()
{
    for (auto &it : components)
    {
        it->Render();
    }
}
bool GameObject::IsDead()
{
    return isDead;
}
void GameObject::RequestDelete()
{
    isDead = true;
}
void GameObject::AddComponent(Component *cpt)
{
    if (started)
    {
        cpt->Start();
    }
    components.emplace_back(std::unique_ptr<Component>(cpt));
}
void GameObject::RemoveComponent(Component *cpt)
{
    for (auto it = components.begin(); it != components.end();)
    {
        if (it->get() == cpt)
        {
            it = components.erase(it);
            break; // * Each component should have just 1 pointer.
        }
        else
        {
            it++;
        }
    }
}
Component *GameObject::GetComponent(std::string type)
{
    for (auto &cpt : components)
    {
        if (cpt->Is(type))
        {
            return cpt.get();
        }
    }

    return nullptr;
}

bool GameObject::IsEmpty()
{
    return this->components.size() == 0;
}

void GameObject::SetAngle(double newAngle)
{
    angleDeg = (float)newAngle;
}

double GameObject::GetAngle()
{
    return angleDeg;
}

void GameObject::NotifyCollision(GameObject &other)
{
    for (size_t i = 0; i < this->components.size(); i++)
    {
        components[i]->NotifyCollision(other);
    }
}

Vec2 GameObject::getScale()
{
    return this->scale;
}

void GameObject::setScale(Vec2 scale)
{
    this->scale = scale;
}

void GameObject::setBoxCenter(Vec2 center)
{
    this->box.x = center.x - (this->box.w * this->scale.x) / 2;
    this->box.y = center.y - (this->box.h * this->scale.y) / 2;
}

Rect GameObject::getBox()
{
    return this->box;
}

void GameObject::setBoxX(int x)
{
    this->box.x = x;
}

void GameObject::setBoxY(int y)
{
    this->box.y = y;
}

void GameObject::setBoxW(int w)
{
    this->box.w = w;
}

void GameObject::setBoxH(int h)
{
    this->box.h = h;
}

Rect GameObject::getScaledBox()
{
    Rect newBox;
    newBox.x = this->box.x;
    newBox.y = this->box.y;
    newBox.w = this->box.w * this->scale.x;
    newBox.h = this->box.h * this->scale.y;
    return newBox;
}
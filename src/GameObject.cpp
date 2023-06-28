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
    this->box = Rect();
    this->components = std::vector<std::unique_ptr<Component>>(); 
    
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
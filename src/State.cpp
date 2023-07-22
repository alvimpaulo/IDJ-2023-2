#include "State.hpp"

State::State()
{
    this->quitRequested = false;
    this->popRequested = false;
    this->started = false;
}

State::~State()
{
    objectArray.clear();
}

std::weak_ptr<GameObject> State::AddObject(GameObject *object)
{
    objectArray.emplace_back(object);

    if (started)
    {
        object->Start();
    }

    return GetObjectPtr(object);
}
std::weak_ptr<GameObject> State::GetObjectPtr(GameObject *object)
{
    for (auto &it : objectArray)
    {
        if ((it).get() == object)
        {
            return std::weak_ptr<GameObject>(it);
        }
    }

    return std::weak_ptr<GameObject>();
}

bool State::PopRequested(){
    return this->popRequested;
}

bool State::QuitRequested(){
    return this->quitRequested;
}

bool State::IsStarted(){
    return this->started;
}

void State::RenderArray(){
    for (size_t i = 0; i < objectArray.size(); i++)
    {
        objectArray[i]->Render();
    }
    
}

void State::UpdateArray(float dt){
    for (size_t i = 0; i < objectArray.size(); i++)
    {
        objectArray[i]->Update(dt);
    }
    
}

void State::StartArray(){
    for (size_t i = 0; i < objectArray.size(); i++)
    {
        objectArray[i]->Start();
    }
    
}
#include "Vec2.hpp"
#include <queue>
#include <string>
#include "Component.hpp"

class Alien : public Component
{
private:
    class Action
    {
    public:
        enum ActionType
        {
            MOVE,
            SHOOT
        };
        Action(ActionType type, float x, float y);
        ActionType type;
        Vec2 pos;
    };

    Vec2 speed;
    int hp;
    int nMinions;
    std::queue<Action> taskQueue;
    std::vector<std::weak_ptr<GameObject>> minionArray;

public:
    Alien(GameObject &associated, int nMinions);
    ~Alien();
    void Start();
    void Update(float dt);
    void Render();
    bool Is(std::string type);
};

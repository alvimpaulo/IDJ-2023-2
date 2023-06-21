#include "Component.hpp"
#include "Vec2.hpp"

class Bullet : public Component
{
private:
    Vec2 speed;
    float distanceLeft;
    int damage;
    
public:
    Bullet(GameObject &associated,
           float angle,
           float speed,
           int damage,
           float maxDistance,
           std::string sprite);
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    int GetDamage();
};

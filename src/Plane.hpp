#include <SFML/Graphics.hpp>
#include "Entity.hpp"

class Plane : public Entity {
  public:
    Plane(sf::Vector2f size, float speed, int bullets, int bombs, int firerate);
    bool shoot();
};


#include <SFML/Graphics.hpp>
#include "Entity.hpp"

class Artillery : public Entity {
  public:
    Artillery(sf::Vector2f size, float speed, int bullets, int bombs, int firerate);
    bool shoot();
};


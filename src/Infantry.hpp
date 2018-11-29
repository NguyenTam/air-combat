#include <SFML/Graphics.hpp>
#include "Entity.hpp"

class Infantry : public Entity {
  public:
    Infantry(sf::Vector2f size, float speed, int bullets, int bombs, int firerate);
    bool shoot();
};

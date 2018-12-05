#include "Ground.hpp"

Ground::Ground(b2World &w,  b2Body &b, const sf::Texture &t, const sf::Vector2f &position):Entity(w, b, t, position, 0.f, 0, 0, 0, 99999){ }


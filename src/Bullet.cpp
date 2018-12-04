#include "Bullet.hpp"

Bullet::Bullet(b2World &w,  b2Body &b, const sf::Texture &t, const sf::Vector2f &position):Entity(w, b, t,position, 50, 0, 0, 0){ }


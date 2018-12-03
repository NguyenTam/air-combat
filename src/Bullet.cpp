#include "Bullet.hpp"

Bullet::Bullet(b2World &w,  b2Body &b, const sf::Texture &t, const sf::Vector2f &position, float speed, int bullets, int bombs, int firerate):Entity(w, b, t,position, speed = 5, bullets = 0, bombs = 0, firerate = 0){ }


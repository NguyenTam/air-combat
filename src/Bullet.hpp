/**
  *   @file Bullet.hpp
  *   @brief Header for Bullet class
  */

#pragma once

/* Includes */

#include "Entity.hpp"
#include <SFML/Graphics.hpp>

/**
  *   @class Bullet
  *   @brief Entity based Bullets
  *   @details Bullets are shoot to other entities to cause damage and destroy those
  */

class Bullet : public Entity {
 public:

 /*
  *   @brief Standard constructor for Bullet
  *   @param w Gameworld where bullet is created in
  *   @param b Bullet's body for collisions
  *   @param t Bullet's texture
  *   @param position Place as vector where bullet is created
  *   @param direction Direction where bullet is headed
  */
  Bullet(b2World &w, b2Body *b, const sf::Texture &t, const sf::Vector2f &position, sf::Vector2f direction);
  Bullet(b2World &w, b2Body *b, const sf::Texture &t, const sf::Vector2f &position, sf::Vector2f direction, Entity* owner);

};

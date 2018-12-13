/**
 *   @file Ground.hpp
 *   @brief Header for Ground class
 */
#pragma once

/* Includes */

#include <SFML/Graphics.hpp>
#include "Entity.hpp"

/**
  *   @class Ground
  */

class Ground : public Entity {
  public:

  /**
   *   @brief Construct a Ground object.
   *   @param w Gameworld where Ground is created in
   *   @param b Grounds body for collisions
   *   @param t Grounds texture
   *   @param position Place as vector where Ground is created
   */
  Ground(b2World &w,  b2Body *b, const sf::Texture &t, const sf::Vector2f &position);
};

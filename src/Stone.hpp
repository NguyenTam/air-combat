/**
 *   @file Stone.hpp
 *   @brief Header for Stone class
 */
#pragma once

/* Includes */

#include <SFML/Graphics.hpp>
#include "Entity.hpp"

/**
  *   @class Stone
  *   @brief Entity based stones
  *   @details Used to block movement of the ground troops. Can be destroyed
  */

class Stone : public Entity {
  public:

  /**
   *   @brief Construct a Stone object.
   *   @param w Gameworld where stone is created in
   *   @param b stones body for collisions
   *   @param t stones texture
   *   @param position Place as vector where stone is created
   */
  Stone(b2World &w,  b2Body *b, const sf::Texture &t, const sf::Vector2f &position);
};

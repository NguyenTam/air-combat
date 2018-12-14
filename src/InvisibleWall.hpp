/**
 *   @file InvisibleWall.hpp
 *   @brief Header for InvisibleWall class
 */
#pragma once

/* Includes */

#include <SFML/Graphics.hpp>
#include "Entity.hpp"

/**
  *   @class InvisibleWall
  *   @brief Entity based InvisibleWall objects
  *   @details These objects are used to create invisble walls at the edges of a level
  */

class InvisibleWall : public Entity {
  public:

  /**
   *   @brief Construct a InvisibleWall object.
   *   @param w Gameworld where InvisibleWall is created in
   *   @param b InvisibleWall body for collisions
   *   @param t InvisibleWall texture
   *   @param position Place as vector where InvisibleWall is created
   */
  InvisibleWall(b2World &w,  b2Body *b, const sf::Texture &t, const sf::Vector2f &position);
};

/**
 *   @file Base.hpp
 *   @brief Header for Base class
 */
#pragma once

/* Includes */

#include <SFML/Graphics.hpp>
#include "Entity.hpp"

/**
  *   @class Base
  */

class Base : public Entity {
  public:

  /**
   *   @brief Construct a Base object.
   *   @param w Gameworld where base is created in
   *   @param b bases body for collisions
   *   @param t bases texture
   *   @param position Place as vector where base is created
   *   @param team Bases team
   */
  Base(b2World &w,  b2Body *b, const sf::Texture &t, const sf::Vector2f &position, Game::TEAM_ID team);
};

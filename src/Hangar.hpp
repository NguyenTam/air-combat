/**
 *   @file Hangar.hpp
 *   @brief Header for Hangar class
 */
#pragma once

/* Includes */

#include <SFML/Graphics.hpp>
#include "Entity.hpp"

/**
  *   @class Hangar
  */

class Hangar : public Entity {
  public:

  /**
   *   @brief Construct a Hangar object.
   *   @param w Gameworld where Hangar is created in
   *   @param b Hangars body for collisions
   *   @param t Hangars texture
   *   @param position Place as vector where Hangar is created
   *   @param team Hangars team
   */
  Hangar(b2World &w,  b2Body &b, const sf::Texture &t, const sf::Vector2f &position, Game::TEAM_ID team);
};

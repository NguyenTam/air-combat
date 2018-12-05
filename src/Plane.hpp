/**
 *   @file Plane.hpp
 *   @brief Header for Plane class
 */
#pragma once

/* Includes */

#include <SFML/Graphics.hpp>
#include "Entity.hpp"

/**
  *   @class Plane
  */

class Plane : public Entity {
  public:

  /**
   *   @brief Construct a Plane object.
   *   @param w Gameworld where plane is created in
   *   @param b Planes body for collisions
   *   @param t Planes texture
   *   @param position Place as vector where Plane is created
   */
  Plane(b2World &w, b2Body &b, const sf::Texture &t, const sf::Vector2f &position, sf::Vector2f direct, Game::TEAM_ID team);
  
  /**
   *   @brief give permission for object to shoot
   *   @return Return true or false based on if the object can shoot or not
   */
  bool shoot();
};


/**
 *   @file Infantry.hpp
 *   @brief Header for Infantry class
 */
#pragma once

/* Includes */

#include <SFML/Graphics.hpp>
#include "Entity.hpp"

/**
  *   @class Infantry
  */

class Infantry : public Entity {
  public:

  /**
   *   @brief Construct a Infantry object.
   *   @param w Gameworld where infantry is created in
   *   @param b infantrys body for collisions
   *   @param t infantrys texture
   *   @param position Place as vector where infantry is created
   */
  Infantry(b2World &w, b2Body &b, const sf::Texture &t, const sf::Vector2f &position);

   /**
     *   @brief give permission for object to shoot
     *   @return Return true or false based on if the object can shoot or not
     */
  bool shoot();
};

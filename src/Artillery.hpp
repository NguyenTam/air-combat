/**
 *   @file Artillery.hpp
 *   @brief Header for Artillery class
 */
#pragma once

/* Includes */

#include <SFML/Graphics.hpp>
#include "Entity.hpp"

/**
  *   @class Artillery
  */

class Artillery : public Entity {
  public:

  /**
   *   @brief Construct a Artillery object.
   *   @param w Gameworld where artillery is created in
   *   @param b Artillerys body for collisions
   *   @param t Artillerys texture
   *   @param position Place as vector where artillery is created
   */
  Artillery(b2World &w,  b2Body &b, const sf::Texture &t, const sf::Vector2f &position);

    /**
     *   @brief give permission for object to shoot
     *   @return Return true or false based on if the object can shoot or not
     */
    bool shoot();
};


/**
 *   @file Artillery.hpp
 *   @brief Header for Artillery class
 */
#pragma once

/* Includes */

#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "Bullet.hpp"
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
   *   @param team Artillerys team
   */
  Artillery(b2World &w,  b2Body *b, const sf::Texture &t, const sf::Vector2f &position, Game::TEAM_ID team);

    /**
     *   @brief give permission for object to shoot
     *   @return Return true or false based on if the object can shoot or not
     */
  virtual bool shoot(sf::Vector2f direction, ResourceManager& resources) override;
};

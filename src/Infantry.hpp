/**
 *   @file Infantry.hpp
 *   @brief Header for Infantry class
 */
#pragma once

/* Includes */

#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "Bullet.hpp"
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
   *   @param team infantrys team
   */
  Infantry(b2World &w, b2Body &b, const sf::Texture &t, const sf::Vector2f &position, Game::TEAM_ID team);
  
  virtual void moveLeft() override;
  
  virtual void moveRight() override;

   /**
     *   @brief give permission for object to shoot
     *   @return Return true or false based on if the object can shoot or not
     */
  virtual bool shoot(sf::Vector2f direction, ResourceManager& resources)  override;
};

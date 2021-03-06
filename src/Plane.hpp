/**
 *   @file Plane.hpp
 *   @brief Header for Plane class
 */
#pragma once

/* Includes */

#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include <Box2D/Box2D.h>
#include "ResourceManager.hpp"
#include "Bullet.hpp"
/**
  *   @class Plane
  *   @brief Entity based planes
  *   @details Planes can eiher be player controlled or AI controlled. They are the
  *   most important entities within air combat game: in both single player and multiplayer goal is
  *   to destroy enemy planes
  */

class Plane : public Entity {
  public:

  /**
   *   @brief Construct a Plane object.
   *   @param w Gameworld where plane is created in
   *   @param b Planes body for collisions
   *   @param t Planes texture
   *   @param position Place as vector where Plane is created
   *   @param direct Direction where plane is headed
   *   @param team Team where plane belongs to
   */
  Plane(b2World &w, b2Body *b, const sf::Texture &t, const sf::Vector2f &position, sf::Vector2f direct, Game::TEAM_ID team);

  virtual void moveUp() override;

  virtual void moveDown() override;

  virtual void moveLeft() override;

  virtual void moveRight() override;


  /**
   *   @brief give permission for object to shoot
   *   @return Return true or false based on if the object can shoot or not
   */
  virtual bool shoot(sf::Vector2f direction, ResourceManager & resources) override;

  void addToKillList(Entity* killed_entity);
  int getGrandTotalKill();
  std::map<Game::TYPE_ID, int> kill_list;
};

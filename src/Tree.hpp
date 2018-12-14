/**
 *   @file Tree.hpp
 *   @brief Header for Tree class
 */
#pragma once

/* Includes */

#include <SFML/Graphics.hpp>
#include "Entity.hpp"

/**
  *   @class Tree
  *   @brief Entity based trees
  *   @details Used to block movement of the ground troops. Can be destroyed
  */

class Tree : public Entity {
  public:

  /**
   *   @brief Construct a Tree object.
   *   @param w Gameworld where tree is created in
   *   @param b Trees body for collisions
   *   @param t Trees texture
   *   @param position Place as vector where tree is created
   */
  Tree(b2World &w,  b2Body *b, const sf::Texture &t, const sf::Vector2f &position);
};

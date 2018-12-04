/**
 *   @file Entity.hpp
 *   @brief Header for Entity class
 */
#pragma once

/* Includes */

#include <iostream>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "CommonDefinitions.hpp"

/**
  *   @class Entity
  */

class Entity {
public:

  /**
   *   @brief Construct a Entity object.
   *   @param w Gameworld where entity is created in
   *   @param b Entitys body for collisions
   *   @param t Entitys texture
   *   @param position Place as vector where entity is created
   *   @param speed Maximum speed for entity
   *   @param bullets Number of bullets this entity can shoot
   *   @param bombs Number of bombs this entity can drop
   *   @param firerate How many frames does it take for the entity to shoot again, so 60 would mean shooting once per second
   */
  Entity(b2World &w, b2Body &b, const sf::Texture &t, const sf::Vector2f &position,  float speed, int bullets, int bombs, int firerate);

  /**
   *   @brief Draw to window
   *   @param window Window to be drawn into   
   */ 
  void drawTo(sf::RenderWindow &window);

  /*
   *   @brief move entity
   *   @param distance Direction as vector where to move entity  
   */
  void move(sf::Vector2f distance);

  /*
   *   @brief assign a position for entity
   *   @param newPos New position as vector given for entity
   */
  void setPos(sf::Vector2f newPos);

  /*
   *   @brief gives entitys position
   *   @return Returns position of the entity as vector
   */
  sf::Vector2f getPosition() const;

  /*
   *   @brief rotates entity clockwise 
   *   @param degrees to rotate  
   */
  void rotate(float);

  /*
   *   @brief puts entity to certain angle
   *   @param angle Degrees of rotation for entity  
   */
  void setRot(float angle);

  /*
   *   @brief move entity directly upward with it's maximum speed  
   */
  void moveUp();

  /*
   *   @brief move entity directly upward with it's maximum speed  
   */
  void moveDown();

  /*
   *   @brief move entity directly left with it's maximum speed  
   */
  void moveLeft();

  /*
   *   @brief move entity directly right with it's maximum speed  
   */
  void moveRight();

  /*
   *   @brief rotates entity clockwise  
   */
  void rotateClockWise();

  /*
   *   @brief rotates entity counterclockwise  
   */
  void rotateCounterClockWise();

  /*
   *   @brief gives the height element from entitys position vector  
   */
  int getY();

  /*
   *   @brief puts a speed for entity 
   *   @param speed Speed for entity
   */
  void setSpeed(float speed);

  /*
   *   @brief gives the speed of the entity  
   */
  float getSpeed();

  /*
   *   @brief general shoot function for entity, more defined version in subclasses
   */
  bool shoot();

  /*
   *   @brief gives a type for entity  
   */
  void setType(Textures::ID type);

  /*
   *   @brief gives the type of entity  
   */
  Textures::ID getType();

  /*
   *   @brief gives the body of entity  
   */
  b2Body& getB2Body();

  bool setScale(float width, float height);

protected:

    /*  Variables */

  //sf::RectangleShape entity;
  sf::Sprite entity;
  float moveSpeed;
  int numberOfBullets;
  int numberOfBombs;
  int rateOfFire; /**< How many frames must pass until entity is able to fire again */
  int fireCountDown; /**< Value set to rateOfFire when entity shoots, every frame value drops by 1, when value 0 or lower, entity can fire */

  private:
  int hitpoints;
  b2World & world;
  b2Body& b2body;
  Textures::ID type;
};

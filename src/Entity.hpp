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
   *   @param firerate How many frames does it take for the entity to shoot again, so 60 would mean shooting once per second.
   *   @param hp Hitpoint of this entity
   */
  Entity(b2World &w, b2Body &b, const sf::Texture &t, const sf::Vector2f &position,  float speed, int bullets, int bombs, int firerate, int hp, sf::Vector2f direction, Game::TEAM_ID team);

  /**
   *   @brief Draw to window
   *   @param window Window to be drawn into   
   */ 
  void drawTo(sf::RenderWindow &window);

  /*
   *   @brief Move entity
   *   @param Distance Direction as vector where to move entity  
   */
  void move(sf::Vector2f distance);

  /*
   *   @brief Assign a position for entity
   *   @param NewPos New position as vector given for entity
   */
  void setPos(sf::Vector2f newPos);

  /*
   *   @brief Gives entitys position
   *   @return Returns position of the entity as vector
   */
  sf::Vector2f getPosition() const;

  /*
   *   @brief Rotates entity clockwise 
   *   @param Degrees to rotate  
   */
  void rotate(float);

  /*
   *   @brief Puts entity to certain angle
   *   @param Angle Degrees of rotation for entity  
   */
  void setRot(float angle);

  /*
   *   @brief Move entity directly upward with it's maximum speed  
   */
  void moveUp();

  /*
   *   @brief Move entity directly upward with it's maximum speed  
   */
  void moveDown();

  /*
   *   @brief Move entity directly left with it's maximum speed  
   */
  void moveLeft();

  /*
   *   @brief Move entity directly right with it's maximum speed  
   */
  void moveRight();

  /*
   *   @brief Rotates entity clockwise  
   */
  void rotateClockWise();

  /*
   *   @brief Rotates entity counterclockwise  
   */
  void rotateCounterClockWise();

  /*
   *   @brief Gives the height element from entitys position vector  
   */
  int getY();

  /*
   *   @brief Puts a speed for entity 
   *   @param Speed Speed for entity
   */
  void setSpeed(float speed);

  /*
   *   @brief Gives the speed of the entity  
   */
  float getSpeed();

  /*
   *   @brief General shoot function for entity, more defined version in subclasses
   */
  bool shoot();

  /*
   *   @brief Gives a type for entity  
   */
  void setType(Textures::ID type);

  /*
   *   @brief Gives the type of entity  
   */
  Textures::ID getType();

  /*
   *   @brief Gives the body of entity  
   */
  b2Body& getB2Body();

  /*
   *   @brief Gives the body of entity  
   */
  bool setScale(float width, float height);

  /*
   *   @brief Puts scale for entitys body  
   */
  int getHitPoints();

  /*
   *   @brief Activated when entity is damaged
   *   @return True is damage kills the entity, False if entity only loses hitpoints
   */
  bool damage(int damage);

  void setDirection(sf::Vector2f direct);

  sf::Vector2f getDirection();

  Game::TEAM_ID getTeamId();

protected:

    /*  Variables */

  //sf::RectangleShape entity;
  sf::Sprite entity;
  float moveSpeed;
  int numberOfBullets;
  int numberOfBombs;
  int rateOfFire; /**< How many frames must pass until entity is able to fire again */
  int fireCountDown; /**< Value set to rateOfFire when entity shoots, every frame value drops by 1, when value 0 or lower, entity can fire */
  int hitPoints;
  sf::Vector2f direction;
  Game::TEAM_ID teamId; 

  private:
  b2World & world;
  b2Body& b2body;
  Textures::ID type;
};

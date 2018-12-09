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
#include <list>

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
   *   @param direction Direction where entity is moving
   *   @param team The team entity belongs to: blue, red, obstacle or projectile
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

  sf::Vector2f getOriginPosition() const;

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
  virtual void moveUp();

  /*
   *   @brief Move entity directly upward with it's maximum speed  
   */
  virtual void moveDown();

  /*
   *   @brief Move entity directly left with it's maximum speed  
   */
  virtual void moveLeft();

  /*
   *   @brief Move entity directly right with it's maximum speed  
   */
  virtual void moveRight();

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
   *   @return Returns the y-cordinate of entity
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
  virtual bool shoot(sf::Vector2f direction);

  /*
   *   @brief Gives a type for entity  
   */
  void setType(Textures::ID type);

  /*
   *   @brief Gives the type of entity  
   *   @return Returns the texture type of entity
   */
  Textures::ID getType();

  /*
   *   @brief Gives the body of entity  
   *   @return Returns body of entity
   */
  b2Body& getB2Body();

  /*
   *   @brief Scales a picture bigger or smaller 
   *   @param width of map
   *   @param height of map
   *   @return Returns is the scaling succesfull, if either number is 0 or smaller, returns FALSE
   */
  bool setScale(float width, float height);

  /**
   *   @brief Get texture size
   *   @return Returns size as vector
   */
  sf::Vector2u getSize();

  /*
   *   @brief Gives entitys hitpoints
   *   @return Returns hitpoints of entity
   */
  int getHitPoints();

  /*
   *   @brief Activated when entity is damaged
   *   @return True is damage kills the entity, False if entity only loses hitpoints
   *   @param damage Amount of damage to entity
   */
  bool damage(int damage);

  /*
   *   @brief Set a direction for entity
   *   @param direct Direction that is set
   */
  void setDirection(sf::Vector2f direct);

  /*
   *   @brief Gives the direction of entity
   */
  sf::Vector2f& getDirection();

  /*
   *   @brief Gives info if entity is players team, enemy team, neutral or projectile
   */
  Game::TEAM_ID getTeamId();

  /*
   *   @brief Tells what entity subclass entity belongs to, for example stone, airplane or infantry
   */
  Game::TYPE_ID getTypeId();

  /*
   *   @brief Adds entity to the surroundings of this entity 
   *   @param entity Entity to be added to the surroundings-list of this entity
   */
  void insert_surrounding(Entity* entity);

  /*
   *   @brief Clears list of entities surrounding this entity
   */
  void erase_surroundings();

  /*
   *   @brief Gets surrounding entities 
   *   @return List of surrounding entities
   */
  std::list<Entity*>& get_surroundings();

  /*
   *   @brief Puts the sprite of entity to face left
   */
  void faceLeft();

  /*
   *   @brief Puts the sprite of entity to face right
   */
  void faceRight();

  /*
   *   @brief Returns active bullets of this entity
   */
  std::list<std::shared_ptr<Entity>>& get_active_bullets();

protected:

    /*  Variables */

  //sf::RectangleShape entity;
  sf::Sprite entity; /**< Entitys sprite */
  float moveSpeed; /**< Entitys speed */
  int numberOfBullets; /**< Number of bullets entity has left */
  int numberOfBombs; /**< Number of bombs entity has left */
  int rateOfFire; /**< Number of frames that must pass until entity is able to fire again */
  int fireCountDown; /**< Value set to rateOfFire when entity shoots, every frame value drops by 1, when value 0 or lower, entity can fire */
  int hitPoints; /**< Hitpoints of entity, if they are zero or lower entity is destroyed */
  sf::Vector2f direction; /**< Diretion of entitys movement */
  Game::TEAM_ID teamId; /**< Tells if entity is in blue or red team, obstacle or projetile */
  Game::TYPE_ID typeId; /**< Tells what entity subclass entity belongs to, for example stone, airplane or infantry */

  
  b2World & world; /**< World where entity exists */
  b2Body& b2body; /**< Entitys body */
  Textures::ID type; /**< Textures file name without extension */
  std::list<Entity*> surrounding;
  std::list<std::shared_ptr<Entity>> active_bullets;
};

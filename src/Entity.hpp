#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "CommonDefinitions.hpp"
class Entity {
public:
  /**     
   */
  Entity(b2World &w, b2Body &b, const sf::Texture &t, const sf::Vector2f &position,  float speed, int bullets, int bombs, int firerate);
  void drawTo(sf::RenderWindow &window);
  void move(sf::Vector2f distance);
  void setPos(sf::Vector2f newPos);
  sf::Vector2f getPosition() const;
  void rotate(float);
  void setRot(float angle);
  void moveUp();
  void moveDown();
  void moveLeft();
  void moveRight();
  void rotateClockWise();
  void rotateCounterClockWise();
  int getY();
  void setSpeed(float speed);
  float getSpeed();
  bool shoot();
  void setType(Textures::ID type);
  Textures::ID getType();
  b2Body& getB2Body();


protected:
  //sf::RectangleShape entity;
  sf::Sprite entity;
  float moveSpeed;
  int numberOfBullets;
  int numberOfBombs;
  int rateOfFire;
  int fireCountDown;

  
  

  private:
  int hitpoints;
  b2World & world;
  b2Body& b2body;
  Textures::ID type;
};

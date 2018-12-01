#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Entity {
public:
  /**
   */
  Entity(sf::Vector2f size, float speed, int bullets, int bombs, int firerate);
  void drawTo(sf::RenderWindow &window);
  void move(sf::Vector2f distance);
  void setPos(sf::Vector2f newPos);
  sf::Vector2f getPosition();
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


protected:
  sf::RectangleShape entity;
  sf::Vector2f position;
  float moveSpeed;
  int numberOfBullets;
  int numberOfBombs;
  int rateOfFire;
  int fireCountDown;
};

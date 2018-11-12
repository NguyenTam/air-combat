#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Entity {
public:
  /**
   */
  Entity(sf::Vector2f size, float speed = 4.f);
  void drawTo(sf::RenderWindow &window);
  void move(sf::Vector2f distance);
  void setPos(sf::Vector2f newPos);
  void rotate(float);
  void moveUp();
  void moveDown();
  void moveLeft();
  void moveRight();
  void rotateClockWise();
  void rotateCounterClockWise();
  int getY();

private:
  sf::RectangleShape entity;
  float moveSpeed;
};

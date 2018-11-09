#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Entity {
public:
  Entity(sf::Vector2f size)
  {
    entity.setSize(size);
    entity.setFillColor(sf::Color::Green);
  }

  void drawTo(sf::RenderWindow &window)
  {
    window.draw(entity);
  }

  void move(sf::Vector2f distance)
  {
    entity.move(distance);
  }

  void setPos(sf::Vector2f newPos)
  {
    entity.setPosition(newPos);
  }

  int getY()
  { return entity.getPosition().y;}

private:
  sf::RectangleShape entity;
};

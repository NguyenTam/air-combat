#include "Entity.h"

Entity::Entity(sf::Vector2f size, float speed) 
{
  entity.setSize(size);
  entity.setOrigin(size.x/2.f, size.y/2.f);
  entity.setFillColor(sf::Color::Green);
  moveSpeed = speed;
}

void Entity::drawTo(sf::RenderWindow &window)
{
  window.draw(entity);
}

void Entity::moveUp()
{
  entity.move({0,-moveSpeed});
}

void Entity::moveDown()
{
  entity.move({0, moveSpeed});
}

void Entity::moveLeft()
{
  entity.move({-moveSpeed,0});
}

void Entity::moveRight()
{
  entity.move({moveSpeed,0});
}

void Entity::rotateClockWise()
{
  entity.rotate(5.f);
}

void Entity::rotateCounterClockWise()
{
  entity.rotate(-5.f);
}

void Entity::setPos(sf::Vector2f newPos)
{
  entity.setPosition(newPos);
}

void Entity::rotate(float degree) {entity.rotate(degree);}

int Entity::getY() {return entity.getPosition().y;}

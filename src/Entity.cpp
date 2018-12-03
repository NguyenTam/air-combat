#include "Entity.hpp"

Entity::Entity(b2World &w, b2Body &b, const sf::Texture &t, const sf::Vector2f &position, float speed, int bullets, int bombs, int firerate) : world(w), b2body(b)
{
  entity.setTexture(t);
  entity.setPosition(position);
  moveSpeed = speed;
  numberOfBullets = bullets;
  numberOfBombs = bombs;
  rateOfFire = firerate;
  fireCountDown = 0;
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

sf::Vector2f Entity::getPosition() const{
  return entity.getPosition();
}

void Entity::setPos(sf::Vector2f newPos)
{
  entity.setPosition(newPos);
}


void Entity::setRot(float angle) {
  entity.setRotation(angle);
}

void Entity::rotate(float degree) {entity.rotate(degree);}

int Entity::getY() {return entity.getPosition().y;}

float Entity::getSpeed()
{
  return moveSpeed;
}

void Entity::move(sf::Vector2f direction){
  setPos(getPosition() + moveSpeed*direction);
}

bool Entity::shoot() {
  if(numberOfBullets>0){
    numberOfBullets-=1;
    return true;
  } else {return false;}
}

void Entity::setType(Textures::ID t){
  type = t;
}

Textures::ID Entity::getType() {return type;}

b2Body& Entity::getB2Body() {return b2body;}

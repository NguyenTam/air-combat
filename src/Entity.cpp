#include "Entity.hpp"
#include <iostream>

Entity::Entity(b2World &w, b2Body &b, const sf::Texture &t, const sf::Vector2f &position, float speed, int bullets, int bombs, int firerate, int hp, sf::Vector2f direct, Game::TEAM_ID team) : moveSpeed(speed), numberOfBullets(bullets), numberOfBombs(bombs), rateOfFire(firerate), fireCountDown(0), hitPoints(hp), direction(direct), teamId(team), world(w), b2body(b)
{
  entity.setTexture(t);
  entity.setPosition(position);
}

void Entity::drawTo(sf::RenderWindow &window)
{
  window.draw(entity);
}

// Does not move by default
void Entity::moveUp(){}

// Does not move by default
void Entity::moveDown(){}

// Does not move by default
void Entity::moveLeft(){}

// Does not move by default
void Entity::moveRight(){}

// Does not move by default
void Entity::rotateClockWise()
{
  // entity.rotate(5.f);
}

// Does not move by default
void Entity::rotateCounterClockWise(){}

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

sf::Vector2u Entity::getSize()
{
  sf::FloatRect rect =  entity.getGlobalBounds();
  return {static_cast<unsigned int>(rect.width), static_cast<unsigned int>(rect.height)};
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

bool Entity::setScale(float width, float height) {
  if (width > 0) {
    if (height > 0) {
      entity.setScale(width / entity.getTexture()->getSize().x, height / entity.getTexture()->getSize().y);
      return true;
    }
  }
  return false;
}

int Entity::getHitPoints(){
  return hitPoints;
}

void Entity::setDirection(sf::Vector2f direct){
  direction = direct;
}

sf::Vector2f Entity::getDirection(){
  return direction;
}

Game::TEAM_ID Entity::getTeamId(){
  return teamId;
}

Game::TYPE_ID Entity::getTypeId(){
  return typeId;
}

bool Entity::damage(int damage){
  if (hitPoints <= 0) {
    return true;
  } else if (hitPoints > damage) {
    hitPoints = hitPoints - damage;
    return false;
  } else {
    return true;
  }
}

void Entity::insert_surrounding(Entity* entity) {
  surrounding.push_back(entity);
}

void Entity::erase_surroundings() {
  surrounding.clear();
}

std::list<Entity*>& Entity::get_surroundings() {
  return surrounding;
}

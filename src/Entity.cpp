#include "Entity.hpp"

Entity::Entity(b2World &w, b2Body &b, const sf::Texture &t, const sf::Vector2f &position, float speed, int bullets, int bombs, int firerate, int hp, sf::Vector2f direct, Game::TEAM_ID team) : moveSpeed(speed), numberOfBullets(bullets), numberOfBombs(bombs), rateOfFire(firerate), fireCountDown(0), hitPoints(hp), direction(direct), teamId(team), world(w), b2body(b)
{
  entity.setTexture(t);
  entity.setPosition(position);
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

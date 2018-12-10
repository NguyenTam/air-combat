#include "Entity.hpp"
#include <iostream>
#include <assert.h>

Entity::Entity(b2World &w, b2Body &b, const sf::Texture &t, const sf::Vector2f &position, float speed, int bullets, int bombs, int firerate, int hp, sf::Vector2f direct, Game::TEAM_ID team) : moveSpeed(speed), numberOfBullets(bullets), numberOfBombs(bombs), rateOfFire(firerate), fireCountDown(0), hitPoints(hp), direction(direct), teamId(team), world(w), b2body(b)
{
  entity.setTexture(t);
  entity.setPosition(position);
}

/*Entity::~Entity()
{
  owner = nullptr;
}*/

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


void Entity::faceLeft()
{
  sf::Vector2u texture_size = entity.getTexture()->getSize();
  //entity.setTextureRect(sf::IntRect(19, 0, -19, 32));
  entity.setTextureRect(sf::IntRect(texture_size.x, 0, -texture_size.x, texture_size.y));
}
void Entity::faceRight()
{
  sf::Vector2u texture_size = entity.getTexture()->getSize();

  //entity.setTextureRect(sf::IntRect(0, 0, 19, 32));
  entity.setTextureRect(sf::IntRect(0, 0, texture_size.x, texture_size.y));
}

// Does not move by default
void Entity::rotateCounterClockWise(){}

sf::Vector2f Entity::getPosition() const{
  return entity.getPosition();
}

sf::Vector2f Entity::getOriginPosition() const {
  return entity.getOrigin();
}

void Entity::setPos(sf::Vector2f newPos)
{
  assert (newPos.x >= 0 && newPos.x <= Game::WIDTH);
  assert (newPos.y >= 0 && newPos.y <= Game::HEIGHT);
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

bool Entity::shoot(sf::Vector2f direction, ResourceManager& resources) {

  (void) direction;
  (void) resources;
  return false;

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

sf::Vector2f& Entity::getDirection(){
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

std::list<std::shared_ptr<Entity>>& Entity::get_active_bullets() {
  return active_bullets;
}

Entity* Entity::getOwner()
{
  return owner;
}

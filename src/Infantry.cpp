#include "Infantry.hpp"
#define VELOCITY 0.2f

//Note about the magical numbers
//Entity(b2World &w, b2Body &b, const sf::Texture &t, const sf::Vector2f &position, float speed, int bullets, int bombs, int firerate, int hp, sf::Vector2f direct, Game::TEAM_ID team) 
Infantry::Infantry(b2World &w, b2Body &b, const sf::Texture &t, const sf::Vector2f &position, Game::TEAM_ID team):Entity(w, b, t, position, 2.f, 200, 0, 300, 3, sf::Vector2f(1.0f, 0.0f), team){ 
  typeId = Game::TYPE_ID::infantry;
  }
   
void Infantry::moveLeft()
{
  b2Vec2 vel = b2body.GetLinearVelocity();
  vel.x = -VELOCITY;
  b2body.SetLinearVelocity(vel);
  direction.x = -1;
  direction.y = 0;

  faceLeft();
}

void Infantry::moveRight()
{
  b2Vec2 vel = b2body.GetLinearVelocity();
  vel.x = VELOCITY;
  b2body.SetLinearVelocity(vel);

  direction.x = 1;
  direction.y = 0;

  faceRight();
}



bool Infantry::shoot(sf::Vector2f direction, ResourceManager& resources){
  if (fireCountDown <= 0) {
    if (numberOfBullets > 0) {
      fireCountDown = rateOfFire;
      numberOfBullets-=1;
      return true;      
    }
  }
  fireCountDown-=1;
  return false;
}



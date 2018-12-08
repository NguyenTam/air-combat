#include "Plane.hpp"
#define FORCE 0.01f
Plane::Plane(b2World &w,  b2Body &b, const sf::Texture &t, const sf::Vector2f &position, sf::Vector2f direct, Game::TEAM_ID team):Entity(w, b, t, position, 20, 400, 6, 10, 20, direct, team){
  typeId = Game::TYPE_ID::airplane;
  }

void Plane::moveUp()
{
  b2body.ApplyLinearImpulse(b2Vec2(0,-FORCE),b2body.GetPosition(),true);
}

void Plane::moveDown()
{
  b2body.ApplyLinearImpulse(b2Vec2(0, FORCE),b2body.GetPosition(), true);
}

void Plane::moveLeft()
{
  b2body.ApplyLinearImpulse(b2Vec2(-FORCE,0),b2body.GetPosition(), true);
}

void Plane::moveRight()
{
  b2body.ApplyLinearImpulse(b2Vec2(FORCE,0),b2body.GetPosition(), true);
}


bool Plane::shoot(){
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

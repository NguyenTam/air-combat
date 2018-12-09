#include "Plane.hpp"
#define MAX_FORCE .5f
#define MAX_VELOCITY 0.5


//Note about the magical numbers
//Entity(b2World &w, b2Body &b, const sf::Texture &t, const sf::Vector2f &position, float speed, int bullets, int bombs, int firerate, int hp, sf::Vector2f direct, Game::TEAM_ID team) 
Plane::Plane(b2World &w,  b2Body &b, const sf::Texture &t, const sf::Vector2f &position, sf::Vector2f direct, Game::TEAM_ID team):Entity(w, b, t, position, 20, 400, 6, 10, 20, direct, team){
  typeId = Game::TYPE_ID::airplane;
  }



void Plane::moveUp()
{
  b2Vec2 vel = b2body.GetLinearVelocity();
  float force = 0;
  if( vel.y > - MAX_VELOCITY )
    {
      force = - MAX_FORCE;
    }
  direction.y = -1;
  b2body.ApplyForce( b2Vec2(0,force), b2body.GetWorldCenter(), true );  
}

void Plane::moveDown()
{
  b2Vec2 vel = b2body.GetLinearVelocity();
  float force = 0;
  if( vel.y < MAX_VELOCITY )
    {
      force = MAX_FORCE;
    }
  direction.y = 1;
  b2body.ApplyForce( b2Vec2(0,force), b2body.GetWorldCenter(), true );
}

void Plane::moveLeft()
{
  b2Vec2 vel = b2body.GetLinearVelocity();
  float force = 1;
  if( vel.x > -MAX_VELOCITY )
    {
      force = -MAX_FORCE;
    }
  faceLeft();
  direction.x = -1;
  b2body.ApplyForce( b2Vec2(force,0), b2body.GetWorldCenter(), true );
}

void Plane::moveRight()
{
  b2Vec2 vel = b2body.GetLinearVelocity();
  float force = 0;
  if( vel.x < MAX_VELOCITY )
    {
      force = MAX_FORCE;
    }
  faceRight();
  direction.x = 1;  
  b2body.ApplyForce( b2Vec2(force,0), b2body.GetWorldCenter(), true );
}


bool Plane::shoot(sf::Vector2f direction){
   
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

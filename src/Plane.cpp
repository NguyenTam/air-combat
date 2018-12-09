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

          ResourceManager resources;

          double x, y;

          if (direction.x < 0) {
            x = getPosition().x - (this->getSize().x)/2;
            y = getPosition().y - (this->getSize().y)/2;
          }

          else {
            x = getPosition().x + (this->getSize().x)/2;
            y = getPosition().y + (this->getSize().y)/2;
          }

          sf::Texture &tex = resources.get(Textures::alphaTextures.at("Bullet"));
          
          b2BodyDef BodyDef;
          BodyDef.type = b2_dynamicBody;
          BodyDef.position = b2Vec2((x+((this->getSize().x)/2))/Game::TOPIXELS, (y+(this->getSize().y)/2)/Game::TOPIXELS);
          BodyDef.bullet = true;

          b2Body* body = world.CreateBody(&BodyDef);

          b2PolygonShape Shape;
          Shape.SetAsBox(((this->getSize().x)/2)/Game::TOPIXELS, ((this->getSize().y)/2)/Game::TOPIXELS); 

          b2FixtureDef FixtureDef;
          FixtureDef.density = 0.f;
          FixtureDef.shape = &Shape;
          FixtureDef.filter.categoryBits = 0x0002;
          body->CreateFixture(&FixtureDef);
          
          sf::Vector2f pos(x,y);
          Bullet bullet(world, *body, tex, pos, sf::Vector2f(1.0f, 0.0f));

          body->SetGravityScale(0.5f);
          body->ApplyLinearImpulse(b2Vec2(10*direction.x, 10*direction.y), body->GetWorldCenter(), true);
          active_bullets.push_back(bullet);
          

          return true;
        }
    }
    fireCountDown-=1;
    return false;
}

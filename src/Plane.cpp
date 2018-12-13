#include "Plane.hpp"
#include "CommonDefinitions.hpp"
#include <cmath>

const int bullet_correction = 3;  // this is how many pixels away from the body bullet is created
const float bullet_force = 1000;  // this is multiplier for impulse given to bullet

//Note about the magical numbers
//Entity(b2World &w, b2Body &b, const sf::Texture &t, const sf::Vector2f &position, float speed, int bullets, int bombs, int firerate, int hp, sf::Vector2f direct, Game::TEAM_ID team)
Plane::Plane(b2World &w,  b2Body &b, const sf::Texture &t, const sf::Vector2f &position, sf::Vector2f direct, Game::TEAM_ID team):Entity(w, b, t, position, 20, 400, 6, 20, 20999, direct, team){
  typeId = Game::TYPE_ID::airplane;
  }



void Plane::moveUp()
{
  b2Vec2 vel = b2body.GetLinearVelocity();
  float force = 0;
  if( vel.y > - Game::Plane::MAX_VELOCITY )
    {
      force = - Game::Plane::MAX_FORCE;
    }
  direction.y = -1;
  b2body.ApplyForce( b2Vec2(0,force), b2body.GetWorldCenter(), true );
}

void Plane::moveDown()
{
  b2Vec2 vel = b2body.GetLinearVelocity();
  float force = 0;
  if( vel.y < Game::Plane::MAX_VELOCITY )
    {
      force = Game::Plane::MAX_FORCE;
    }
  direction.y = 1;
  b2body.ApplyForce( b2Vec2(0,force), b2body.GetWorldCenter(), true );
}

void Plane::moveLeft()
{
  b2Vec2 vel = b2body.GetLinearVelocity();
  float force = 1;
  if( vel.x > -Game::Plane::MAX_VELOCITY )
    {
      force = -Game::Plane::MAX_FORCE;
    }
  faceLeft();
  direction.x = -1;
  b2body.ApplyForce( b2Vec2(force,0), b2body.GetWorldCenter(), true );
}

void Plane::moveRight()
{
  b2Vec2 vel = b2body.GetLinearVelocity();
  float force = 0;
  if( vel.x < Game::Plane::MAX_VELOCITY )
    {
      force = Game::Plane::MAX_FORCE;
    }
  faceRight();
  direction.x = 1;
  b2body.ApplyForce( b2Vec2(force,0), b2body.GetWorldCenter(), true );
}


bool Plane::shoot(sf::Vector2f direction, ResourceManager & resources){

  if (clock.getElapsedTime()>sf::seconds(0.5f)) {
        if (numberOfBullets > 0) {
          //fireCountDown = rateOfFire;
          numberOfBullets-=1;

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
          std::cout << "Plane location X: " << x << " Y: " << y << " Size X: " << this->getSize().x << " Y: " << this->getSize().y << std::endl;
          if (direction.y < 0 && -(direction.y) >= std::abs(direction.x)) {  //shooting up
            if (direction.x > 0) {
              x -= (this->getSize().x)/4;
 	      y -= 4*(this->getSize().y)/3;
	    }
            BodyDef.position = b2Vec2((x+((this->getSize().x)/2))/Game::TOPIXELS, (y-bullet_correction)/Game::TOPIXELS);
            std::cout << "Bullet created up X: " << (x+((this->getSize().x)/2)) << " Y: " << (y-bullet_correction) << std::endl;
          }
          else if (direction.y > 0 && direction.y >= std::abs(direction.x)){  //shooting down
            if (direction.x > 0) {
              x -= (this->getSize().x)/2;
              y -= (this->getSize().y)/2;
	    }
            BodyDef.position = b2Vec2((x+((this->getSize().x)/2))/Game::TOPIXELS, (y+(this->getSize().y)+bullet_correction+5)/Game::TOPIXELS);
            std::cout << "Bullet created down X: " << (x+((this->getSize().x)/2)) << " Y: " << (y+(this->getSize().y)+bullet_correction) << std::endl;
          }
          else if (direction.x > 0 && direction.x >= std::abs(direction.y)){  //shooting right
            if (direction.y > 0) {
              y += 2*(this->getSize().y)/3;
              x -= (this->getSize().x)/4;
	    }
            y -= (this->getSize().y)/2;
            BodyDef.position = b2Vec2((x+(this->getSize().x)/2+bullet_correction)/Game::TOPIXELS, (y)/Game::TOPIXELS);
            std::cout << "Bullet created right X: " << (x+(this->getSize().x)+bullet_correction) << " Y: " << (y-((this->getSize().y)/2)) << std::endl;
          }
          else {                                 //shooting left
            if (direction.y > 0) {
              x -= (this->getSize().x)/4;
              y -= (this->getSize().y)/4;
	    }
            x += (this->getSize().x)/2;
            y += (this->getSize().y)/4;
            BodyDef.position = b2Vec2((x-bullet_correction)/Game::TOPIXELS, (y+((this->getSize().y)/2))/Game::TOPIXELS);
            std::cout << "Bullet created left X: " << (x-bullet_correction) << " Y: " << (y+((this->getSize().y)/2)) << std::endl;
          }

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
          std::shared_ptr<Entity> bullet = std::make_shared<Bullet>(world, *body, tex, pos, sf::Vector2f(1.0f, 0.0f), this);
          bullet->setType(Textures::Bullet_alpha);

          body->SetGravityScale(0.5f);
	  //std::cout << "Plane fires, force of bullet: X: " << direction.x*bullet_force << ", Y: " << direction.y*bullet_force << std::endl;
          body->ApplyLinearImpulse(b2Vec2(direction.x*bullet_force, direction.y*bullet_force), body->GetWorldCenter(), true);
          body->SetUserData(bullet.get());
          active_bullets.push_back(bullet);

          clock.restart();
          //std::cout << "airplane shot" << std::endl;
          return true;
        }
    }
  //fireCountDown-=1;
    return false;
}

#include "Plane.hpp"
#include "CommonDefinitions.hpp"
#include <cmath>

const int bullet_correction = 5;  // this is how many pixels away from the body bullet is created
const float bullet_force = 1000;  // this is multiplier for impulse given to bullet


Plane::Plane(b2World &w,  b2Body *b, const sf::Texture &t, const sf::Vector2f &position, sf::Vector2f direct, Game::TEAM_ID team):Entity(w, b, t, position, 20, 400, 6, 20, 20, direct, team){
  typeId = Game::TYPE_ID::airplane;
  }



void Plane::moveUp()
{
  b2Vec2 vel = b2body->GetLinearVelocity();
  float force = 0;
  if( vel.y > - Game::Plane::MAX_VELOCITY )
    {
      force = - Game::Plane::MAX_FORCE;
    }
  direction.y = -1;
  b2body->ApplyForce( b2Vec2(0,force), b2body->GetWorldCenter(), true );
}

void Plane::moveDown()
{
  b2Vec2 vel = b2body->GetLinearVelocity();
  float force = 0;
  if( vel.y < Game::Plane::MAX_VELOCITY )
    {
      force = Game::Plane::MAX_FORCE;
    }
  direction.y = 1;
  b2body->ApplyForce( b2Vec2(0,force), b2body->GetWorldCenter(), true );
}

void Plane::moveLeft()
{
  b2Vec2 vel = b2body->GetLinearVelocity();
  float force = 1;
  if( vel.x > -Game::Plane::MAX_VELOCITY )
    {
      force = -Game::Plane::MAX_FORCE;
    }
  faceLeft();
  direction.x = -1;
  b2body->ApplyForce( b2Vec2(force,0), b2body->GetWorldCenter(), true );
}

void Plane::moveRight()
{
  b2Vec2 vel = b2body->GetLinearVelocity();
  float force = 0;
  if( vel.x < Game::Plane::MAX_VELOCITY )
    {
      force = Game::Plane::MAX_FORCE;
    }
  faceRight();
  direction.x = 1;
  b2body->ApplyForce( b2Vec2(force,0), b2body->GetWorldCenter(), true );
}


bool Plane::shoot(sf::Vector2f direction, ResourceManager & resources){

  if (clock.getElapsedTime()>sf::seconds(0.5f)) {
        if (numberOfBullets > 0) {
          numberOfBullets-=1;

          double x, y;

          if (getFacing()) {
            x = getPosition().x + (this->getSize().x)/2*cos(this->getB2Body()->GetAngle()) + bullet_correction;
            y = getPosition().y + (this->getSize().y)/2*sin(this->getB2Body()->GetAngle());
          }
          else {
            x = getPosition().x - (this->getSize().x)/2*cos(this->getB2Body()->GetAngle()) - bullet_correction;
            y = getPosition().y - (this->getSize().y)/2*sin(this->getB2Body()->GetAngle());
          }

          sf::Texture &tex = resources.get(Textures::alphaTextures.at("Bullet"));

          b2BodyDef BodyDef;
          BodyDef.type = b2_dynamicBody;

          BodyDef.position = b2Vec2(x*Game::TOMETERS, y*Game::TOMETERS);
          BodyDef.bullet = true;

          b2Body* body = world.CreateBody(&BodyDef);

          b2PolygonShape Shape;
          Shape.SetAsBox(((this->getSize().x)/2)/Game::TOPIXELS, ((this->getSize().y)/2)/Game::TOPIXELS);

          b2FixtureDef FixtureDef;
          FixtureDef.density = 0.f;
          FixtureDef.shape = &Shape;
          FixtureDef.filter.categoryBits = 0x0008;
          body->CreateFixture(&FixtureDef);

          sf::Vector2f pos(x,y);
          std::shared_ptr<Entity> bullet = std::make_shared<Bullet>(world, body, tex, pos, sf::Vector2f(1.0f, 0.0f), this);
          bullet->setType(Textures::Bullet_alpha);

          body->SetGravityScale(0.5f);
          body->ApplyLinearImpulse(b2Vec2(direction.x*bullet_force, direction.y*bullet_force), body->GetWorldCenter(), true);
          body->SetUserData(bullet.get());
          active_bullets.push_back(bullet);

          clock.restart();
          return true;
        }
  }
    return false;
}

void Plane::addToKillList(Entity* killed_entity)
{
  if ( Entity::getTeamId() != killed_entity->getTeamId() )
  {
    kill_list[killed_entity->getTypeId()]++;
  }
}

int Plane::getGrandTotalKill()
{
  int sum = 0;
  for (auto const & entity : kill_list)
  {
    sum += entity.second;
  }
  return sum;
}

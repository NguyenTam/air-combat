#include "Artillery.hpp"
#include <cmath>

const int bullet_correction = 2;  // this is how many pixels away from the body bullet is created
const float bullet_force = 1000;  // this is multiplier for impulse given to bullet

//Entity(b2World &w, b2Body &b, const sf::Texture &t, const sf::Vector2f &position, float speed, int bullets, int bombs, int firerate, int hp, sf::Vector2f direct, Game::TEAM_ID team)
Artillery::Artillery(b2World &w,  b2Body *b, const sf::Texture &t, const sf::Vector2f &position, Game::TEAM_ID team):Entity(w, b, t, position, 0.f, 1000, 0, 90, 30, sf::Vector2f(1.0f, 0.0f), team){
  typeId = Game::TYPE_ID::antiaircraft;
  }

bool Artillery::shoot(sf::Vector2f direction, ResourceManager& resources){
  if (clock.getElapsedTime() > sf::seconds(0.5)) {
        if (numberOfBullets > 0) {
 
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
	  if (-(direction.y) >= (std::abs(direction.x))) {   //shooting up
	    if (direction.x < 0) {
              x += (this->getSize().x)/2;
              y += (this->getSize().y)/3;
	    }
            BodyDef.position = b2Vec2(x/Game::TOPIXELS, (y-bullet_correction-((this->getSize().y)/2))/Game::TOPIXELS);
          }
          else if (direction.x < 0){                         //shooting left
            BodyDef.position = b2Vec2((x-bullet_correction)/Game::TOPIXELS, (y+((this->getSize().y)/2))/Game::TOPIXELS);
          }
          else {                                             //shooting right
            BodyDef.position = b2Vec2((x+(this->getSize().x)+bullet_correction)/Game::TOPIXELS, (y-((this->getSize().y)/2))/Game::TOPIXELS);
          }
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

          numberOfBullets-=1;
          clock.restart();
          return true;
        }
    }
    return false;
}

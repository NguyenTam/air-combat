#include "Artillery.hpp"
#include <cmath>

//Note about the magical numbers
//Entity(b2World &w, b2Body &b, const sf::Texture &t, const sf::Vector2f &position, float speed, int bullets, int bombs, int firerate, int hp, sf::Vector2f direct, Game::TEAM_ID team) 
Artillery::Artillery(b2World &w,  b2Body &b, const sf::Texture &t, const sf::Vector2f &position, Game::TEAM_ID team):Entity(w, b, t, position, 0.f, 1000, 0, 90, 30, sf::Vector2f(1.0f, 0.0f), team){ 
  typeId = Game::TYPE_ID::antiaircraft;
  }

bool Artillery::shoot(sf::Vector2f direction, ResourceManager& resources){
  if (clock.getElapsedTime() > sf::seconds(0.5)) {
        if (numberOfBullets > 0) {
          //fireCountDown = rateOfFire;

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
          if (-(direction.y) >= (std::abs(direction.x))) {
            BodyDef.position = b2Vec2((x+((this->getSize().x)/2))/Game::TOPIXELS, (y-2)/Game::TOPIXELS);
          }
          else if (direction.x < 0){
            BodyDef.position = b2Vec2((x-4)/Game::TOPIXELS, (y+((this->getSize().y)/2))/Game::TOPIXELS);
          }
          else {
            BodyDef.position = b2Vec2((x+(this->getSize().x)+4)/Game::TOPIXELS, (y-((this->getSize().y)/2))/Game::TOPIXELS);
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
          std::shared_ptr<Entity> bullet = std::make_shared<Bullet>(world, *body, tex, pos, sf::Vector2f(1.0f, 0.0f));
          bullet->setType(Textures::Bullet_alpha);

          body->SetGravityScale(0.5f);
          body->ApplyLinearImpulse(b2Vec2(direction.x/5, direction.y/5), body->GetWorldCenter(), true);
          body->SetUserData(bullet.get());
          active_bullets.push_back(bullet);      
          
          numberOfBullets-=1;
          clock.restart();
          std::cout << "artillery shot" << std::endl;
          return true;  
        }
    }
  //fireCountDown-=1;
    return false;    
}



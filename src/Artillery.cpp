#include "Artillery.hpp"

//Note about the magical numbers
//Entity(b2World &w, b2Body &b, const sf::Texture &t, const sf::Vector2f &position, float speed, int bullets, int bombs, int firerate, int hp, sf::Vector2f direct, Game::TEAM_ID team) 
Artillery::Artillery(b2World &w,  b2Body &b, const sf::Texture &t, const sf::Vector2f &position, Game::TEAM_ID team):Entity(w, b, t, position, 0.f, 1000, 0, 60, 30, sf::Vector2f(1.0f, 0.0f), team){ 
  typeId = Game::TYPE_ID::antiaircraft;
  }

bool Artillery::shoot(sf::Vector2f direction){
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



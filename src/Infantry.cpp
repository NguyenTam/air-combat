#include "Infantry.hpp"

Infantry::Infantry(b2World &w, b2Body &b, const sf::Texture &t, const sf::Vector2f &position, Game::TEAM_ID team):Entity(w, b, t, position, 2.f, 200, 0, 180, 3, sf::Vector2f(1.0f, 0.0f), team){ 
  typeId = Game::TYPE_ID::infantry;
  }
   
    bool Infantry::shoot(){
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



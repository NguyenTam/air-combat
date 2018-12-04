#include "Artillery.hpp"

Artillery::Artillery(b2World &w,  b2Body &b, const sf::Texture &t, const sf::Vector2f &position):Entity(w, b, t, position, 0.f, 1000, 0, 60){ }

bool Artillery::shoot(){
      if (fireCountDown <= 0) {
        if (numberOfBullets > 0) {
          fireCountDown = rateOfFire;
          numberOfBullets-=1;
          return true;  
        } else {
          return false;
        }
    } else {
      fireCountDown-=1;
      return false;
    }
}



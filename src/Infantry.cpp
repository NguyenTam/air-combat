#include "Infantry.hpp"

Infantry::Infantry(b2World &w, b2Body &b, const sf::Texture &t, const sf::Vector2f &position):Entity(w, b, t, position, 2.f, 200, 0, 180, 3){ }
   
    bool Infantry::shoot(){
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



#include "Plane.hpp"

Plane::Plane(b2World &w,  b2Body &b, const sf::Texture &t, const sf::Vector2f &position):Entity(w, b, t, position, 20, 400, 6, 10){ }

bool Plane::shoot(){
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



#include "Artillery.hpp"

Artillery::Artillery(b2World &w, b2Body &b, const sf::Texture &t, const sf::Vector2f &position, float speed=0.f, int bullets=999, int bombs=0, int firerate = 60):Entity(w, b, t, position, speed, bullets, bombs, firerate){ }

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



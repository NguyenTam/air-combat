#include "Artillery.hpp"

Artillery::Artillery(sf::Vector2f size, float speed, int bullets, int bombs, int firerate):Entity(size, speed = 0.f, bullets = 999, bombs = 0, firerate = 60){ }

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



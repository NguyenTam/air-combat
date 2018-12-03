#include "Infantry.hpp"

Infantry::Infantry(const sf::Texture &t, const sf::Vector2f &position, float speed, int bullets, int bombs, int firerate):Entity(t, position, speed = 2.f, bullets = 999, bombs = 0, firerate = 180){ }
   
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



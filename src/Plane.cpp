#include "Plane.hpp"

Plane::Plane(b2World &w,  b2Body &b, const sf::Texture &t, const sf::Vector2f &position, float speed, int bullets, int bombs, int firerate):Entity(w, b, t, position, speed = 20, bullets = 100, bombs = 6, firerate = 10){ }

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



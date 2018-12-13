#include "Bullet.hpp"

Bullet::Bullet(b2World &w,  b2Body *b, const sf::Texture &t, const sf::Vector2f &position, sf::Vector2f direct):Entity(w, b, t,position, 50, 0, 0, 0, 1, direct, Game::TEAM_ID::all_enemy){
  typeId = Game::TYPE_ID::bullet;
  }

Bullet::Bullet(b2World &w,  b2Body *b, const sf::Texture &t, const sf::Vector2f &position, sf::Vector2f direct, Entity* owner):Entity(w, b, t,position, 50, 0, 0, 0, 1, direct, Game::TEAM_ID::all_enemy){
  typeId = Game::TYPE_ID::bullet;
  this->owner = owner;
  }

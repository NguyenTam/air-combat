#include "Tree.hpp"

Tree::Tree(b2World &w,  b2Body &b, const sf::Texture &t, const sf::Vector2f &position):Entity(w, b, t, position, 0.f, 0, 0, 0, 50, sf::Vector2f(1.0f, 0.0f), Game::TEAM_ID::all_friend){ 
  typeId = Game::TYPE_ID::tree;
  }

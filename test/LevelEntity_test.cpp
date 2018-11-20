/**
  *   @file LevelEntity_test.cpp
  *   @brief Contains small test main for class LevelEntity
  */

#include "../src/LevelEntity.hpp"
#include <assert.h>
#include <iostream>
#include <string>

int main()
{
  std::cout << "LevelEntity TEST" << std::endl;

  // Construct empty objects
  LevelEntity level_entity = LevelEntity();
  std::cout << level_entity;

  float x = 3.4;
  float y = 2;
  std::string img_path = "../data/img/infantry.png";

  for (int i = 0; i < 5; i++)
  {
    level_entity = LevelEntity(i * x, i * y, 40, 40, img_path);
    std::cout << level_entity;
    assert(level_entity.getPosition().x == x*i);
    assert(level_entity.getPosition().y == y*i);
  }

  std::cout << std::endl;
  std::cout << "Image loading should fail but not crash the program" << std::endl;
  LevelEntity entity2 = LevelEntity(43, 668, 50, 50, "");
  entity2.setPosition(100, 459);
  assert(entity2.getPosition() == sf::Vector2f(100, 459));

  entity2.setPosition(sf::Vector2f(30, 50));
  assert(entity2.isInside(45, 56));

  LevelEntity entity3 = LevelEntity(212, 44.6, 78, 10, img_path);
  LevelEntity entity4 = entity3;

  assert(entity4.getPosition() == sf::Vector2f(212, 44.6));

  std::cout << "Asserts ok, test complited succesfully" << std::endl;
  return 0;
}

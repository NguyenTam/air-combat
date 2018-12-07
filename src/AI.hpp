#pragma once
#include "CommonDefinitions.hpp"
#include "Entity.hpp"
#include <tuple>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <list>

namespace AI {
  extern std::map<Game::TYPE_ID, int> priority_list;

  std::tuple<Game::ACTIONS, sf::Vector2f> get_action(Entity& me, std::list<Entity*> &surroundings);
  std::tuple<Game::ACTIONS, sf::Vector2f> get_airplane_action(Entity& me, std::list<Entity*> &surroundings);
  std::tuple<Game::ACTIONS, sf::Vector2f> get_antiaircraft_action(Entity& me, std::list<Entity*> &surroundings);
  std::tuple<Game::ACTIONS, sf::Vector2f> get_infantry_action(Entity& me, std::list<Entity*> &surroundings);
  void set_target(Entity& me, std::list<Entity*> &surroundings, Entity* current_worse_enemy, int &current_worse_enemy_priority);  
}

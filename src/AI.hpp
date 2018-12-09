#pragma once
#include "CommonDefinitions.hpp"
#include "Entity.hpp"
#include <tuple>
#include <list>
#include <cstdlib>

namespace AI {
  extern std::map<Game::TYPE_ID, int> priority_list;
  
  void get_action(Entity& me, std::list<Entity*> &surroundings);
  void get_airplane_action(Entity& me, std::list<Entity*> &surroundings);
  void get_antiaircraft_action(Entity& me, std::list<Entity*> &surroundings);
  void get_infantry_action(Entity& me, std::list<Entity*> &surroundings);
  void set_target(Entity& me, std::list<Entity*> &surroundings, sf::Vector2f & current_worse_enemy, int &current_worse_enemy_priority);
  bool is_too_close(sf::Vector2f & e1, sf::Vector2f & e2);
  void move_to_direction(Entity& me);
}

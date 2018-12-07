#pragma once
#include "CommonDefinitions.hpp"
#include "Entity.hpp"
#include <tuple>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <list>

namespace AI {
  std::map<Game::TYPE_ID, int> priority_list
  {
    { Game::TYPE_ID::airplane, 10 },
    { Game::TYPE_ID::antiaircraft, 7 },
    { Game::TYPE_ID::base, 6 },
    { Game::TYPE_ID::hangar, 5 },
    { Game::TYPE_ID::infantry, 8 },
    { Game::TYPE_ID::bullet, 9 },
    { Game::TYPE_ID::ground, -1 },
    { Game::TYPE_ID::rock, 1 },
    { Game::TYPE_ID::tree, 1 }
  };


  std::tuple<Game::ACTIONS, sf::Vector2f> get_action(Entity& me, std::list<Entity*> &surroundings);
  std::tuple<Game::ACTIONS, sf::Vector2f> get_airplane_action(Entity& me, std::list<Entity*> &surroundings);
  std::tuple<Game::ACTIONS, sf::Vector2f> get_antiaircraft_action(Entity& me, std::list<Entity*> &surroundings);
  std::tuple<Game::ACTIONS, sf::Vector2f> get_infantry_action(Entity& me, std::list<Entity*> &surroundings);
  void set_target(Entity& me, std::list<Entity*> &surroundings, Entity* current_worse_enemy, int &current_worse_enemy_priority);
}

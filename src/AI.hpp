#pragma once
#include "CommonDefinitions.hpp"
#include "Entity.hpp"
#include <tuple>
class AI {
public:
  Game::ACTIONS get_action(Game::TYPE_ID my_type, Game::TEAM_ID my_id, std::map<int, Entity> &surroundings);
private:
  Game::ACTIONS get_airplane_action(Game::TYPE_ID my_type, Game::TEAM_ID my_id, std::map<int, Entity> &surroundings);
  Game::ACTIONS get_antiaircraft_action(Game::TYPE_ID my_type, Game::TEAM_ID my_id, std::map<int, Entity> &surroundings);
  Game::ACTIONS get_infantry_action(Game::TYPE_ID my_type, Game::TEAM_ID my_id, std::map<int, Entity> &surroundings);
};

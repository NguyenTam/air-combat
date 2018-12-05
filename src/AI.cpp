#include "AI.hpp"
Game::ACTIONS AI::get_action(Game::TYPE_ID my_type, Game::TEAM_ID my_id, std::map<int, Entity> &surroundings)
{
  switch (my_type)
    {
    case Game::TYPE_ID::airplane:
      return get_airplane_action(my_type, my_id, surroundings);
      break;
    case Game::TYPE_ID::antiaircraft:
      return get_airplane_action(my_type, my_id, surroundings);
    case Game::TYPE_ID::infantry:
      return get_airplane_action(my_type, my_id, surroundings);
    default:
      return Game::ACTIONS::nothing;
    }
}

Game::ACTIONS AI::get_airplane_action(Game::TYPE_ID my_type, Game::TEAM_ID my_id, std::map<int, Entity> &surroundings)
{
  for ( auto const& item : surroundings )
    {
      
    }
}

Game::ACTIONS AI::get_antiaircraft_action(Game::TYPE_ID my_type, Game::TEAM_ID my_id, std::map<int, Entity> &surroundings)
{
  for ( auto const& item : surroundings )
    {
      
    }  
}
Game::ACTIONS AI::get_infantry_action(Game::TYPE_ID my_type, Game::TEAM_ID my_id, std::map<int, Entity> &surroundings)
{
  for ( auto const& item : surroundings )
    {
      
    }  
}

#include "AI.hpp"
namespace AI
{
  std::tuple<Game::ACTIONS, sf::Vector2f> get_action(Entity& me, std::list<Entity*> &surroundings)
  {
    srand(time(nullptr));
    switch (me.getTypeId())
      {
      case Game::TYPE_ID::airplane:
	return get_airplane_action(me, surroundings);
      case Game::TYPE_ID::antiaircraft:
	return get_airplane_action(me, surroundings);
      case Game::TYPE_ID::infantry:
	return get_airplane_action(me, surroundings);
      default:
	return std::make_tuple(Game::ACTIONS::nothing, sf::Vector2f(0,0));
      }
  }

  std::tuple<Game::ACTIONS, sf::Vector2f> get_airplane_action(Entity& me, std::list<Entity*> &surroundings)
  {
    Entity* current_worse_enemy;
    int current_worse_enemy_priority;
    sf::Vector2f my_position = me.getPosition();
    set_target(me, surroundings, current_worse_enemy, current_worse_enemy_priority);
    if( my_position.x < 10 || my_position.x > 0.1 * Game::WIDTH || my_position.y < 10 || my_position.x > 0.6 * Game::HEIGHT ||  current_worse_enemy_priority == priority_list[Game::TYPE_ID::ground] )
      {
      
	if ( my_position.x < 10 )
	  {
	    return std::make_tuple(Game::ACTIONS::move_right, Game::actions_and_directions[Game::ACTIONS::move_right]);
	  }
	else if ( my_position.x > 0.1 * Game::WIDTH )
	  {
	    return std::make_tuple(Game::ACTIONS::move_left, Game::actions_and_directions[Game::ACTIONS::move_left]);
	  }
	else if ( my_position.y < 10 )
	  {
	    return std::make_tuple(Game::ACTIONS::move_down, Game::actions_and_directions[Game::ACTIONS::move_down]);
	  }
	else if ( my_position.y > 0.6 * Game::HEIGHT )
	  {
	    return std::make_tuple(Game::ACTIONS::move_up, Game::actions_and_directions[Game::ACTIONS::move_up]);
	  }
	else
	  {
	    Game::ACTIONS movement_action = static_cast<Game::ACTIONS>(random()%4);
	    return std::make_tuple(movement_action, Game::actions_and_directions[movement_action] );
	  }
      }
    else if (current_worse_enemy != nullptr)
      {
	switch (current_worse_enemy->getTypeId())
	  {
	  case Game::TYPE_ID::airplane :
	    {
	      sf::Vector2f direction = my_position - current_worse_enemy->getPosition();
	      return std::make_tuple(Game::ACTIONS::shoot, direction);
	    }
	  default:
	    {
	      return std::make_tuple(Game::ACTIONS::bomb, Game::actions_and_directions[Game::ACTIONS::bomb]);
	    }
	  }      
      }
    else {return std::make_tuple(Game::ACTIONS::nothing, Game::actions_and_directions[Game::ACTIONS::nothing]);}
  }

  std::tuple<Game::ACTIONS, sf::Vector2f> get_antiaircraft_action(Entity& me, std::list<Entity*> &surroundings)
  {
    Entity* current_worse_enemy;
    int current_worse_enemy_priority;
    sf::Vector2f my_position = me.getPosition();
    set_target(me, surroundings, current_worse_enemy, current_worse_enemy_priority);
    if ((current_worse_enemy != nullptr) && (current_worse_enemy->getTypeId() == Game::TYPE_ID::airplane))
      {
	sf::Vector2f direction = my_position - current_worse_enemy->getPosition();
	return std::make_tuple(Game::ACTIONS::shoot, direction);
      }
    else
      {
	return std::make_tuple(Game::ACTIONS::nothing, Game::actions_and_directions[Game::ACTIONS::nothing]);
      }
  }

  std::tuple<Game::ACTIONS, sf::Vector2f> get_infantry_action(Entity& me, std::list<Entity*> &surroundings)
  {
    Entity* current_worse_enemy;
    int current_worse_enemy_priority;
    sf::Vector2f my_position = me.getPosition();
    set_target(me, surroundings, current_worse_enemy, current_worse_enemy_priority);
    if( my_position.x < 10 || my_position.x > 0.1 * Game::WIDTH || my_position.y < 10 || my_position.x > 0.6 * Game::HEIGHT ||  current_worse_enemy_priority == priority_list[Game::TYPE_ID::ground] )
      {
      
	if ( my_position.x < 10 )
	  {
	    return std::make_tuple(Game::ACTIONS::move_right, Game::actions_and_directions[Game::ACTIONS::move_right]);
	  }
	else if ( my_position.x > 0.1 * Game::WIDTH )
	  {
	    return std::make_tuple(Game::ACTIONS::move_left, Game::actions_and_directions[Game::ACTIONS::move_left]);
	  }
	else
	  {
	    Game::ACTIONS movement_action = static_cast<Game::ACTIONS>(random()%2);
	    return std::make_tuple(movement_action, Game::actions_and_directions[movement_action] );
	  }
      }
    else if (current_worse_enemy != nullptr)
      {
	sf::Vector2f direction = my_position - current_worse_enemy->getPosition();
	return std::make_tuple(Game::ACTIONS::shoot, direction);
      }
    else {return std::make_tuple(Game::ACTIONS::nothing, Game::actions_and_directions[Game::ACTIONS::nothing]);}
  }
  
  void set_target(Entity& me, std::list<Entity*> &surroundings, Entity* current_worse_enemy, int &current_worse_enemy_priority)
  {
    current_worse_enemy = nullptr;
    current_worse_enemy_priority = -1;
    for ( auto const& e : surroundings )
      {
	Game::TYPE_ID surrounding_type = e->getTypeId();
	Game::TEAM_ID surrounding_team_id = e->getTeamId();
	if ( (surrounding_team_id != Game::TEAM_ID::all_friend) && (surrounding_team_id != me.getTeamId()) )
	  {
	    if ( priority_list[surrounding_type] > current_worse_enemy_priority )
	      {
		current_worse_enemy = e;
		current_worse_enemy_priority = priority_list[surrounding_type];
	      }
	  }
      }
  }
}

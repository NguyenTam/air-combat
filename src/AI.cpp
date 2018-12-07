#include "AI.hpp"
namespace AI
{
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
    if( my_position.x < Game::LEFT_LIMIT || my_position.x > Game::RIGHT_LIMIT || my_position.y < Game::LOWER_LIMIT || my_position.x > Game::UPPER_LIMIT ||  current_worse_enemy_priority == priority_list[Game::TYPE_ID::ground] )
      {

	if ( my_position.x < Game::LEFT_LIMIT )
	  {
	    me.moveRight();
	    return std::make_tuple(Game::ACTIONS::move_right, Game::actions_and_directions[Game::ACTIONS::move_right]);
	  }
	else if ( my_position.x > Game::RIGHT_LIMIT )
	  {
	    me.moveLeft();
	    return std::make_tuple(Game::ACTIONS::move_left, Game::actions_and_directions[Game::ACTIONS::move_left]);
	  }
	else if ( my_position.y < Game::LOWER_LIMIT )
	  {
	    me.moveDown();
	    return std::make_tuple(Game::ACTIONS::move_down, Game::actions_and_directions[Game::ACTIONS::move_down]);
	  }
	else if ( my_position.y > Game::UPPER_LIMIT )
	  {
	    me.moveUp();
	    return std::make_tuple(Game::ACTIONS::move_up, Game::actions_and_directions[Game::ACTIONS::move_up]);
	  }
	else
	  {
	    Game::ACTIONS movement_action = static_cast<Game::ACTIONS>(random()%4);
	    switch (movement_action)
	      {
	      case Game::ACTIONS::move_left:
		me.moveLeft();
		break;
	      case Game::ACTIONS::move_right:
		me.moveRight();
		break;
	      case Game::ACTIONS::move_up:
		me.moveUp();
		break;
	      default:
		me.moveDown();
		break;
	      }
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
    return std::make_tuple(Game::ACTIONS::nothing, Game::actions_and_directions[Game::ACTIONS::nothing]);
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
      return std::make_tuple(Game::ACTIONS::nothing, Game::actions_and_directions[Game::ACTIONS::nothing]);
  }

  std::tuple<Game::ACTIONS, sf::Vector2f> get_infantry_action(Entity& me, std::list<Entity*> &surroundings)
  {
    Entity* current_worse_enemy;
    int current_worse_enemy_priority;
    sf::Vector2f my_position = me.getPosition();
    set_target(me, surroundings, current_worse_enemy, current_worse_enemy_priority);
    if( my_position.x < Game::LEFT_LIMIT || my_position.x > Game::RIGHT_LIMIT ||  current_worse_enemy_priority == priority_list[Game::TYPE_ID::ground] )
      {

	if ( my_position.x < Game::LEFT_LIMIT )
	  {
	    me.moveRight();
	    return std::make_tuple(Game::ACTIONS::move_right, Game::actions_and_directions[Game::ACTIONS::move_right]);
	  }
	else if ( my_position.x > Game::RIGHT_LIMIT )
	  {
	    me.moveLeft();
	    return std::make_tuple(Game::ACTIONS::move_left, Game::actions_and_directions[Game::ACTIONS::move_left]);
	  }
	else
	  {
	    Game::ACTIONS movement_action = static_cast<Game::ACTIONS>(random()%2);
	    switch (movement_action)
	      {
	      case Game::ACTIONS::move_left:
		me.moveLeft();
		break;
	      default:
		me.moveRight();
		break;
	      }
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
} // namespace AI

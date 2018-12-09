#include "AI.hpp"
#include <cmath>
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
    { Game::TYPE_ID::ground, 0 },
    { Game::TYPE_ID::rock, 1 },
    { Game::TYPE_ID::tree, 1 }
  };
  void get_action(Entity& me, std::list<Entity*> &surroundings)
  {   
    switch (me.getTypeId())
      {
      case Game::TYPE_ID::airplane:
	return get_airplane_action(me, surroundings);
      case Game::TYPE_ID::antiaircraft:
	return get_antiaircraft_action(me, surroundings);
      case Game::TYPE_ID::infantry:
	return get_infantry_action(me, surroundings);
      default:
	return ;
      }
  }
    void move_to_direction(Entity& me)
    {
      sf::Vector2f directions = me.getDirection();
      if (directions.x > 0)
	me.moveRight();
      if (directions.x < 0)
	me.moveLeft();
      if (directions.y > 0)
	me.moveDown();
      if (directions.y < 0)
	me.moveUp();
    }
  // NOTICE current_worse_enemy was supposed to be Entity pointer, but we encountered a nasty problem: right after set_target-function call current_worse_enemy was assigned back to null pointer???
  void get_airplane_action(Entity& me, std::list<Entity*> &surroundings)
  {
    sf::Vector2f current_worse_enemy = {-1.f,-1.f};
    int current_worse_enemy_priority = -1;
    sf::Vector2f my_position = me.getPosition();
    //std::cout << "Surroundings size: " << surroundings.size() << std::endl;
    set_target(me, surroundings, current_worse_enemy, current_worse_enemy_priority);
    //std::cout << " ########################" << std::endl;
    if( my_position.x < Game::LEFT_LIMIT || my_position.x > Game::RIGHT_LIMIT || my_position.y < Game::LOWER_LIMIT || my_position.x > Game::UPPER_LIMIT )
      {
	if ( my_position.x < Game::LEFT_LIMIT )
	  {	    
	    me.moveRight();
	  }
	if ( my_position.x > Game::RIGHT_LIMIT )
	  {
	    me.moveLeft();
	  }
	if ( my_position.y < Game::LOWER_LIMIT )
	  {
	    me.moveDown();
	  }
	if ( my_position.y > Game::UPPER_LIMIT )
	  {	   
	    me.moveUp();
	  }
	move_to_direction(me);
	 /*
	else
	  {	    
	    if (me.getDirection().x > 0)
	      me.moveLeft();
	    else me.moveRight();
	  }
	 */
      }
    // If worse enemy is visible
    if (current_worse_enemy.x > 0)
      {
	std::cout << "Enemy found at at (x,y): " << current_worse_enemy.x << ", " << current_worse_enemy.y << std::endl;
	switch (current_worse_enemy_priority)
	  {
	  case 10:
	    {
	      sf::Vector2f direction = my_position - current_worse_enemy;
	      me.shoot(direction);
	      std::cout << "shot at (x,y): " << current_worse_enemy.x << ", " << current_worse_enemy.y << std::endl;
	      return;
	    }
	  default:
	    {
	      me.shoot({0.f, 1.f});
	      std::cout << "bomb at (x,y): " << current_worse_enemy.x << ", " << current_worse_enemy.y << std::endl;
	      return;
	    }
	  }
      }
    else
      {
	move_to_direction(me);
      }
  }

  void get_antiaircraft_action(Entity& me, std::list<Entity*> &surroundings)
  {
    sf::Vector2f current_worse_enemy =  {-1.0f,-1.0};
    int current_worse_enemy_priority = -1;
    sf::Vector2f my_position = me.getPosition();
    set_target(me, surroundings, current_worse_enemy, current_worse_enemy_priority);
    if ((current_worse_enemy.x > 0) && (current_worse_enemy_priority > 0) && (current_worse_enemy.y  > 10))
      {
	sf::Vector2f direction = my_position - current_worse_enemy;
	me.shoot(direction);
      }
  }

  void get_infantry_action(Entity& me, std::list<Entity*> &surroundings)
  {
    sf::Vector2f current_worse_enemy = {-1.0f,-1.0};
    int current_worse_enemy_priority = 0;
    sf::Vector2f my_position = me.getPosition();
    set_target(me, surroundings, current_worse_enemy, current_worse_enemy_priority);
    if( my_position.x < Game::LEFT_LIMIT || my_position.x >= Game::RIGHT_LIMIT )
      {
	if ( my_position.x < Game::LEFT_LIMIT )
	  {
	    me.moveRight();
	  }
	else 
	  {
	    me.moveLeft();
	  }
      }
    else
      // Target exist
      if (current_worse_enemy.x > 0 )
	{
	  // Target is enemy => shoot and move to opposite direction
	  if(current_worse_enemy_priority > 0)
	    {
	      sf::Vector2f direction = my_position - current_worse_enemy;
	      me.shoot(direction);
	      std::cout << "shot called!!" <<  std::endl;
	      if(direction.x > 0)
		me.moveRight();
	      else me.moveLeft();
	    }
	  // Target is friend => move to opposite direction
	  else if (current_worse_enemy_priority < 0) {
	    sf::Vector2f new_direction = my_position - current_worse_enemy;

	    // far away => walk to other direction
	    if (is_too_close(my_position, current_worse_enemy) || new_direction.x > 0)
	      me.moveRight();
	    else me.moveLeft();
	  }
	  else {}
	}    
      else
	{	
	  if (me.getDirection().x > 0)
	    me.moveRight();
	  else me.moveLeft();
	}
  }

  void set_target(Entity& me, std::list<Entity*> &surroundings, sf::Vector2f& current_worse_enemy, int &current_worse_enemy_priority)
  {

    float longest_distance = -1.f;
    for ( Entity* e : surroundings )
      {
	Game::TYPE_ID surrounding_type = e->getTypeId();
	Game::TEAM_ID surrounding_team_id = e->getTeamId();

	//std::cout << surrounding_team_id << std::endl;
	if ( surrounding_team_id != Game::TEAM_ID::all_friend )
	  {
	    if (surrounding_team_id != me.getTeamId())
	      {
		if (priority_list[surrounding_type] > current_worse_enemy_priority)
		  {
		    current_worse_enemy = e->getPosition();
		    current_worse_enemy_priority = priority_list[surrounding_type];
		  }
	      }
	    // same team.
	    else if (surrounding_team_id == me.getTeamId())
	      {
		sf::Vector2f distance = me.getPosition() - e->getPosition();
		float distance_length = std::sqrt(distance.x*distance.x + distance.y*distance.y);
		if (current_worse_enemy.x < 0 )
		  {
		    longest_distance = distance_length;
		    current_worse_enemy = e->getPosition();
		    current_worse_enemy_priority = -priority_list[surrounding_type];
		  }
		else if (distance_length > longest_distance)
		  {
		    longest_distance = distance_length;
		    current_worse_enemy = e->getPosition();		   
		    current_worse_enemy_priority = -priority_list[surrounding_type];
		  }
	      }
	  }
	else
	  {
	    if ( current_worse_enemy.x < 0 )
	      {
		current_worse_enemy = e->getPosition();
		current_worse_enemy_priority = -priority_list[surrounding_type];		
	      }
	  }
      }
  }

  bool is_too_close(sf::Vector2f & e1, sf::Vector2f & e2)
  {
    sf::Vector2f distance = e1-e2;
    return std::sqrt(distance.x*distance.x + distance.y*distance.y) < 10;
  }
} // namespace AI

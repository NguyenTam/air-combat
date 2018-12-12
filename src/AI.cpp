#include "AI.hpp"
#include <cmath>
#include <cstdlib>
#include <math.h> 
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
void get_action(Entity& me, std::list<Entity*> &surroundings, ResourceManager & resources)
  {   
    switch (me.getTypeId())
      {
      case Game::TYPE_ID::airplane:
	return get_airplane_action(me, surroundings, resources);
      case Game::TYPE_ID::antiaircraft:
	return get_antiaircraft_action(me, surroundings, resources);
      case Game::TYPE_ID::infantry:
	return get_infantry_action(me, surroundings,resources);
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
void get_airplane_action(Entity& me, std::list<Entity*> &surroundings, ResourceManager & resources)
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
            me.moveRight();
	  }
	if ( my_position.x > Game::RIGHT_LIMIT )
	  {
	    me.moveLeft();
            me.moveLeft();
	  }
	if ( my_position.y < Game::LOWER_LIMIT )
	  {
	    me.moveDown();
            me.moveDown();
	  }
	if ( my_position.y > Game::UPPER_LIMIT )
	  {	   
	    me.moveUp();
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
	//std::cout << "Target found at at (x,y): " << current_worse_enemy.x << ", " << current_worse_enemy.y << std::endl;
	if (current_worse_enemy_priority > 0)
	  {
	    switch (current_worse_enemy_priority)
	      {
	      case 10:
		{
		  sf::Vector2f direction = current_worse_enemy - my_position;
                  float scale = sqrt(pow(std::abs(direction.x),2)+pow(std::abs(direction.y),2));
                  direction.x = direction.x/scale;
                  direction.y = direction.y/scale;
		  me.shoot(direction, resources);
		  //std::cout << "shot direction (x,y): " << direction.x << ", " << direction.y << std::endl;
		  return;
		}
	      default:
		{                  
                  me.shoot(sf::Vector2f(0.f, 1.f), resources);		  
		  return;
		}
	      }
	  }
	else if ( current_worse_enemy_priority < 0 )
	  {
	    //std::cout << "friendly entity detected. avoid it. " << std::endl;

            if (current_worse_enemy.y <= my_position.y)
            {
              me.moveDown();
            }
            if (current_worse_enemy.y > my_position.y)
            {
              me.moveDown();
            }
            if (current_worse_enemy.x < my_position.x)
            {
              me.moveRight();
            }
            if (current_worse_enemy.x >= my_position.x)
            {
              me.moveLeft();
            }
                
            /*
	    switch (std::rand()%2)
	      {
	      case 0:
		{
		  me.moveDown();
		  me.moveDown();
		}
	      default:
		me.moveUp();
		me.moveDown();
	      }
            */
	  }
	else move_to_direction(me);
      }
    else
      {
	move_to_direction(me);
      }
  }

void get_antiaircraft_action(Entity& me, std::list<Entity*> &surroundings, ResourceManager & resources)
  {
    sf::Vector2f current_worse_enemy =  {-1.0f,-1.0};
    int current_worse_enemy_priority = -1;
    sf::Vector2f my_position = me.getPosition();
    set_target(me, surroundings, current_worse_enemy, current_worse_enemy_priority);
    if ((current_worse_enemy.x > 0) && (current_worse_enemy_priority > 0) && (current_worse_enemy.y  > 10))
      {
	sf::Vector2f direction = current_worse_enemy - my_position;
        float scale = sqrt(pow(std::abs(direction.x),2)+pow(std::abs(direction.y),2));
        direction.x = direction.x/scale;
        direction.y = direction.y/scale;
	me.shoot(direction, resources);
      }
  }

void get_infantry_action(Entity& me, std::list<Entity*> &surroundings, ResourceManager & resources)
  {
    sf::Vector2f current_worse_enemy = {-1.0f,-1.0};
    int current_worse_enemy_priority = 0;
    sf::Vector2f my_position = me.getPosition();
    set_target(me, surroundings, current_worse_enemy, current_worse_enemy_priority);
    const int EPSILON = 50;
    if( my_position.x < EPSILON || my_position.x >= Game::WIDTH - EPSILON)
      {
	if ( my_position.x < EPSILON )
	  {
	    me.moveRight();
	  }
	else
	  {
	    me.moveLeft();
	  }
      }
    // Target exist
    if (current_worse_enemy.x > 0 )
      {
	// Target is enemy => shoot and move to opposite direction
	if(current_worse_enemy_priority > 0)
	  {
	    sf::Vector2f direction =  current_worse_enemy - my_position;
            float scale = sqrt(pow(std::abs(direction.x),2)+pow(std::abs(direction.y),2));
            direction.x = direction.x/scale;
            direction.y = direction.y/scale;
	    me.shoot(direction, resources);
	    if(direction.x > 0)
	      me.moveLeft();
	    else me.moveRight();
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
	    current_worse_enemy = e->getPosition();
	    current_worse_enemy_priority = priority_list[surrounding_type];
	  }
      }
  }

  bool is_too_close(sf::Vector2f & e1, sf::Vector2f & e2)
  {
    sf::Vector2f distance = e1-e2;
    return std::sqrt(distance.x*distance.x + distance.y*distance.y) < 10;
  }
} // namespace AI

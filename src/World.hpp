/**
  *   @file World.hpp
  *   @brief Header for World class
  */

#pragma once

#include "Entity.hpp"
#include "PhysicsWorld.hpp"
#include "ResourceManager.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <vector>
#include <Box2D/Box2D.h>
#include <fstream>
#include <sstream>


#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#define TOPIXELS 60.0
#define TOMETERS 1/TOPIXELS


/**
  *   @class World
  *   @brief World class for air combat game
  */

//This class presents the game view. 

class World {
public:
	/**
      *   @brief Constructor for World
      *   @details creates variable for used window
      *   @param main_window RenderWindow which is used to display the game
      */
	World(sf::RenderWindow &main_window, ResourceManager &resources);

	/**
      *   @brief Adds given entity to the game
      *   @param entity Pointer to the entity that is being added
      *   @return Returns true if succesful, false if not
      */
	bool add_entity(Entity *entity);

	/**
      *   @brief Removes given entity from the game
      *   @param entity Pointer to the entity that is being removed
      *   @return Returns true if succesful, false if not
      */
	bool remove_entity(Entity *entity);

	/**
      *   @brief Updates the world
      *   @details Is called from the game engine
      */
	void update();

  bool read_level(std::string filename);

  void clear_all();

private:
  PhysicsWorld pworld;
	sf::RenderWindow &window; /**< Window that is being used */
	std::vector<Entity*> objects; /**< Contains all the entities added */
};

/**
  *   @file World.hpp
  *   @brief Header for World class
  */

#pragma once

#include "Entity.hpp"
#include "PhysicsWorld.hpp"
#include "ResourceManager.hpp"
#include "CommonDefinitions.hpp"
#include "Plane.hpp"
#include "Artillery.hpp"
#include "Infantry.hpp"
#include "Bullet.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <vector>
#include <Box2D/Box2D.h>
#include <fstream>
#include <sstream>


#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f



/**
  *   @class World
  *   @brief World class for air combat game
  */

//This class presents the game view. 

class World {
public:

  World() = delete;
  World& operator=(World &other);
	/**
      *   @brief Constructor for World
      *   @details creates variable for used window
      *   @param main_window RenderWindow which is used to display the game
      */
	World(sf::RenderWindow &main_window, ResourceManager &_resources);

	/**
      *   @brief Adds given entity to the game
      *   @param type: string of entity's type, x: x-axis coordinate, y: y-axis coordinate, orientation: direction where the entity is facing, width: width of the entity, height: height of the entity
      *   @return Returns true if succesful, false if not
      */

	bool create_entity(Textures::ID id, double x, double y, int orientation, double width, double height);

	/**
      *   @brief Removes given entity from the game
      *   @param entity Pointer to the entity that is being removed
      *   @return Returns true if succesful, false if not
      */
	bool remove_entity(std::shared_ptr<Entity> entity);

	/**
      *   @brief Updates the world
      *   @details Is called from the game engine
      */
	void update();

  bool read_level(std::string& filename);

  void clear_all();

private:
  PhysicsWorld pworld;
  ResourceManager &resources;
	sf::RenderWindow &window; /**< Window that is being used */
	std::vector<std::shared_ptr<Entity>> objects; /**< Contains all the entities added */
};

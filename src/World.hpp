/**
  *   @file World.hpp
  *   @brief Header for World class
  */

#pragma once

/* Includes */

#include "Entity.hpp"
#include "PhysicsWorld.hpp"
#include "ResourceManager.hpp"
#include "CommonDefinitions.hpp"
#include "Plane.hpp"
#include "Artillery.hpp"
#include "Infantry.hpp"
#include "Bullet.hpp"
#include "Tree.hpp"
#include "Stone.hpp"
#include "Base.hpp"
#include "Ground.hpp"
#include "Hangar.hpp"
#include "AI.hpp"
#include "InvisibleWall.hpp"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <vector>
#include <Box2D/Box2D.h>
#include <fstream>
#include <sstream>
#include <list>
#include <deque>


#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f


enum GameResult
{
  UnFinished,
  BlueWon,
  RedWon,
  TieGame
};


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
      *   @param _resources Resources given by ResourceManager
      */
	World(sf::RenderWindow &main_window, ResourceManager &_resources);

	/**
      *   @brief Adds given entity to the game
      *   @param id: string of entity's type
      *   @param x: x-axis coordinate
      *   @param y: y-axis coordinate
      *   @param orientation: direction where the entity is facing
      *   @param width: width of the entity
      *   @param height: height of the entity
      *   @param direct: direction where entity is headed
      *   @param game_mode: single- or multiplayer
      *   @return Returns true if succesful, false if not
      */
	bool create_entity(Textures::ID id, double x, double y, int orientation, double width, double height, sf::Vector2f direct, Game::GameMode game_mode);

  bool remove_bullet(Entity *bullet, Entity *entity);
	/**
      *   @brief Removes given entity from the game
      *   @param entity Raw pointer to the entity that is being removed
      *   @param bullet Pass true if bullet is to be removed, false otherwise
      *   @return Returns true if succesful, false if not
      */
	bool remove_entity(Entity *entity);

	/**
      *   @brief Updates the world
      *   @details Is called from the game engine
      *   @param game_mode Current Game::GameMode
      *   @return Returns GameResult
      */
	GameResult update(Game::GameMode game_mode);

	/**
      *   @brief Reads the given level
      *   @details Is called from the game engine
      *   @param filename Filename of level to be opened
      *   @param game_mode Is the game multiplayer or singleplayer
      */
        bool read_level(std::string& filename, Game::GameMode game_mode);

	/**
      *   @brief Clears all entitys
      *   @details Is called from the game engine when new game is started
      */
        void clear_all();

	/**
      *   @return Returns all objects
      */
        std::vector<std::shared_ptr<Entity>>& get_all_entities();

	/**
      *   @return Returns all planes controlled by player
      */
        std::deque<std::shared_ptr<Entity>>& get_player_planes();


        /**
          *   @brief Get score,
          *   @remark This should be used only during singleplayer
          *   @return Returns score
          */
        int getScore();

        /**
          *   @brief Find Entity
          *   @param Box2D body of the entity
          *   @return Returns raw pointer to the entity
          */
        Entity* findEntity(b2Body *body);

private:

  /**
    *   @brif Check game status
    *   @return Returns correct GameResult
    *   @param game_mode Current Game::GameMode
    */
  GameResult checkGameStatus(Game::GameMode game_mode);

  PhysicsWorld pworld;
  ResourceManager &resources;
  sf::RenderWindow &window; /**< Window that is being used */
  std::vector<std::shared_ptr<Entity>> objects; /**< Contains all the entities added */
  std::deque<std::shared_ptr<Entity>> player_planes; /**< Contains BlueAirplane and during multiplayer also one RedAirplane */
  std::list<b2Body*> destroyed_entity_bodies; /**< Destroyed entity bodies which should be removed from the world */
  std::list<b2Body*> destroyed_bullet_bodies; /**< Destroyed bullet bodies which should be removed from the world */
  int score = 0;
};

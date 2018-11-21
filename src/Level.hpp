/**
  *   @file Level.hpp
  *   @brief Header for class Level
  */

#pragma once

/*  Includes  */

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <memory>
#include <string>
#include "LevelEntity.hpp"


/*  Macros */

#define NO_ENTITY 0 /**< This has to be same as LevelEntity type default value */
#define PLANE_ENTITY 1 /**< Entity type for planes */
#define INFANTRY_ENTITY 2 /**< Entity type for infantry */
#define ERASE_ENTITY -1 /**< Entity type for erasing entities */



/**
  *   @class Level
  *   @brief Class used to create a level to air combat
  *   @details Contains LevelEntities and methods to update entities. Level
  *   can also create or open a file
  *   @remark Level coordinate system (origin) differs from LevelEditor
  */
class Level
{
  public:

    /**
      *   @brief Standard constructor for Level
      *   @param y_limit The lowest allowed point y position for objects
      */
    Level();

    /**
      *   @brief Set level_y_limit
      *   @param y_limit New level_y_limit
      *   @remark This need to be set after construction
      */
    void setYLimit(float y_limit);

    /**
      *   @brief Move current_entity
      *   @details Moves current_entity if it isn't positioned
      *   @param x Level x coordinate
      *   @param y Level y coordinate
      */
    void moveCurrentEntity(float x, float y);

    /**
      *   @brief Add LevelEntity to Level
      *   @details This method is called from LevelEditor after user has clicked
      *   and wants to add a new object to the level
      *   @param x Level x coordinate
      *   @param y Level y coordinate
      *   @param entity_type LevelEntity type, use Macros from Level.hpp
      *   @remark This is a wrapper call for AddPlane, AddInfantry etc.
      */
    void addEntity(float x, float y, int entity_type);

    /**
      *   @brief Draw Level
      *   @param window RenderWindow where the Level is drawn
      */
    void drawLevel(sf::RenderWindow &window);

    /**
      *   @brief Remove current_entity from level_entities
      *   @details Doesn't remove current if it's positioned, in this case
      *   assigns an empty entity to current_entity
      */
    void removeCurrent();


  private:

    /**
      *   @brief Check if position is free
      *   @details Checks all four corners of the object
      *   @return Returns true if free
      *   @param x x coordinate
      *   @param y y coordinate
      *   @param width New LevelEntity width
      *   @param height New LevelEntity height
      *   @param cmp LevelEntity which is moving and is obviously not checked
      */
    bool CheckPosition(float x, float y, float width, float height, LevelEntity *cmp);

    /**
      *   @brief Try to add an infantry entity
      *   @details If current_entity is positioned or not an infantry entity
      *   creates new infantry entity. Otherwise, tries to fully position
      *   current_entity
      *   @param x Level x coordinate
      *   @param y Level y coordinate
      */
    void AddInfantry(float x, float y);

    /**
      *   @brief Try to add a plane entity
      *   @details If current_entity is positioned or not a plane entity
      *   creates new plane entity. Otherwise, tries to fully position
      *   current_entity
      *   @param x Level x coordinate
      *   @param y Level y coordinate
      */
    void AddPlane(float x, float y);

    /**
      *   @brief Try to remove a LevelEntity
      *   @param x Level x coordinate
      *   @param y Level y coordinate
      */
    void EraseEntity(float x, float y);


    /*  Variables */
    float level_y_limit = 0; /**< Tells level y limit (i.e. the lowest allowed point to place entities) */
    std::shared_ptr<LevelEntity> current_entity;
    float current_entity_height = 0;
    std::vector<std::shared_ptr<LevelEntity>> level_entities; /**< All LevelEntities */

    /* These are just temporary */
    float infantry_width = 40;
    float infantry_height = 40;
    const std::string infantry_path = "../data/img/infantry.png";

    float plane_width = 40;
    float plane_height = 40;
    const std::string plane_path = "../data/img/plane.png";
};

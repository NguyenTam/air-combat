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
#include <iostream>
#include <fstream>
#include <experimental/filesystem>
#include "LevelEntity.hpp"


/*  Macros */

#define NO_ENTITY 0 /**< This has to be same as LevelEntity type default value */
#define FRIENDLY_PLANE 1 /**< Entity type for friendly planes */
#define FRIENDLY_INFANTRY 2 /**< Entity type for friendly infantry */
#define ERASE_ENTITY -1 /**< Entity type for erasing entities */
#define HOSTILE_PLANE 3 /**< Entity type for hostile planes */
#define HOSTILE_INFANTRY 4 /**< Entity type for hostile infantry */
#define FRIENDLY_AA 5 /**< Entity type for frindly AA */
#define HOSTILE_AA 6 /**< Entity type for hostile AA */
#define FRIENDLY_HANGAR 7 /**< Entity type for friendly hangar */
#define HOSTILE_HANGAR 8 /**< Entity type for hostile hangar */
#define FRIENDLY_BASE 9 /**< Entity type for friendly base */
#define HOSTILE_BASE 10 /**< Entity type for hostile base */
#define TREE_ENTITY 11 /**< Entity type for tree */
#define ROCK_ENTITY 12 /**< Entity type for rock */



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

    /**
      *   @brief Flip / unflip LevelEntity
      *   @details Calls LevelEntity flipLevelEntity for LevelEntity matching
      *   x and y coordinates. Does nothing if no entity matches the coordinates
      *   @param x Level x coordinate
      *   @param y Level y coordinate
      */
    void flipEntity(float x, float y);

    /**
      *   @brief Output level to ostream
      *   @details Used to write Level to file
      *   @param os Output stream
      *   @param level Level to be written to the stream
      */
    friend std::ostream& operator<<(std::ostream &os, const Level &level);

    /**
      *   @brief Save Level to file
      *   @details If file is opened in non-truncate mode and it exits,
      *   returns false
      *   @param level_name is filename (.txt added by Level)
      *   @param description Level description (saved to the file)
      *   @param truncate Whether file is truncated or not if it exists
      *   @return On success, returns true. Otherwise false
      */
    bool saveToFile(std::string level_name, std::string description, bool truncate);

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
      *   @brief Try to add LevelEntity
      *   @details Called from addEntity to do the adding task itself
      *   @param x Level x coordinate
      *   @param y Level y coordinate
      *   @param entity_type LevelEntity type (see Macros)
      *   @param entity_width Type matching width
      *   @param entity_height Type matching height
      *   @param entity_img Path to image file for matching entity_type
      */
    void AddEntity(float x, float y, int entity_type, float entity_width, float entity_height, std::string entity_img);

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

    /* Every entity width, height and path */
    float infantry_width = 19;
    float infantry_height = 32;
    const std::string friendly_infantry_path = "../data/img/BlueInfantry_alpha.png";
    const std::string hostile_infantry_path = "../data/img/RedInfantry_alpha.png";

    float plane_width = 38;
    float plane_height = 18;
    const std::string friendly_plane_path = "../data/img/BlueAirplane_alpha.png";
    const std::string hostile_plane_path = "../data/img/RedAirplane_alpha.png";

    float AA_width = 36;
    float AA_height = 31;
    const std::string friendly_AA_path = "../data/img/BlueAntiAircraft_alpha.png";
    const std::string hostile_AA_path = "../data/img/RedAntiAircraft_alpha.png";

    float hangar_width = 28;
    float hangar_height = 26;
    const std::string friendly_hangar_path = "../data/img/BlueHangar_alpha.png";
    const std::string hostile_hangar_path = "../data/img/RedHangar_alpha.png";

    float base_width = 76;
    float base_height = 63;
    const std::string friendly_base_path = "../data/img/BlueBase_alpha.png";
    const std::string hostile_base_path = "../data/img/RedBase_alpha.png";

    float tree_width = 27;
    float tree_height = 36;
    const std::string tree_path = "../data/img/tree_alpha.png";

    float rock_width = 25;
    float rock_height = 20;
    const std::string rock_path = "../data/img/rock_alpha.png";

};

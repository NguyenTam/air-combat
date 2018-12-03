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
#include "ResourceManager.hpp"


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
#define GROUND_ENTITY 13 /**< Entity type for ground */

/*#define ground_height 100
#define ground_width 100*/

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


    /* Every entity width, height */
    static const float infantry_width;
    static const float infantry_height;
    static const float plane_width;
    static const float plane_height;
    static const float AA_width;
    static const float AA_height;
    static const float hangar_width;
    static const float hangar_height;
    static const float base_width;
    static const float base_height;
    static const float tree_width;
    static const float tree_height;
    static const float rock_width;
    static const float rock_height;
    static const float ground_width;
    static const float ground_height;



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
      *   @brief Draw Level to RenderTexture
      *   @param texture RenderTexture where Level is drawn
      *   @remark This is used to create an image of the Level
      */
    void drawTexture(sf::RenderTexture &texture);

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

    /**
      *   @brief Finish adding ground entity
      *   @details Locks current ground entity into place. This should be called
      *   from LevelEditor::place_ground_action()
      *   @return Returns true if ground was added
      */
    bool finishAddingGround();

    /**
      *   @brief Get Level width
      *   @details Goes through all level_entities and returns the right most
      *   point of the level
      *   @return Returns the right most x coordinate
      */
    float getLevelWidth() const;

    /**
      *   @brief Parse Level from levelfile
      *   @param levelfile Path to Level file
      *   @details Clears whole Level first and then adds LevelEntities based on the
      *   file
      *   @remark File format needs to follow level file format
      *   (espicially comment symbols are needed even though comment
      *   would be an empty string)
      *   @return Returns true if level was successfully parsed
      */
    bool parseLevel(std::string& levelfile);

    /**
      *   @brief Clear all LevelEntities from Level
      */
    void clearAll();

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
    void AddEntity(float x, float y, int entity_type, float entity_width, float entity_height, sf::Texture &texture);

    /**
      *   @brief Try to remove a LevelEntity
      *   @param x Level x coordinate
      *   @param y Level y coordinate
      */
    void EraseEntity(float x, float y);

    /**
      *   @brief Add ground entity
      *   @param x Level x coordinate
      *   @param y Level y coordinate
      *   @remark Ground entities are special so they require own add function
      */
    void AddGround(float x, float y);

    /**
      *   @brief Update ground level
      *   @details Call this when new ground object is being placed
      *   @param x_left LevelEntity left corner x coordinate
      *   @param x_right LevelEntity right corner x coordinate
      *   @param y LevelEntity top corner y coordinate
      */
    void UpdateGroundLevel(unsigned x_left, unsigned x_right, unsigned y);

    /**
      *   @brief Get ground level below entity
      *   @param entity_x LevelEntity x coordinate
      *   @param entity_width LevelEntity width
      *   @param entity_height LevelEntity height
      *   @remark LevelEntities are allowed to be added 1 pixel above ground
      */
    unsigned GetGroundLevel(float entity_x, float entity_width, float entity_height);

    /**
      *   @brief Remove LevelEntities below position
      *   @details Doesn't remove Ground entities. This is used when Ground is
      *   fully_constructed to remove entities below the Ground
      *   @param x Level x coordinate
      *   @param y Level y coordinate
      *   @param width LevelEntity width
      *   @param height LevelEntity height
      *   @remark Somewhat heavy operation
      */
    void RemoveEntitiesBelow(float x, float y, float width, float height);

    /**
      *   @brief Remove Ground entity related ground_level entries
      *   @param ground Ground object pointer (entity must still exist)
      */
    void RemoveGround(std::shared_ptr<LevelEntity> ground);

    /**
      *   @brief Get new ground level
      *   @details This should be called when ground entity is removed
      *   @param x LevelEntity x coordinate on Level
      *   @param ground Ground enitity which isn't compared
      *   @remark Quite heavy operation, use sparingly
      */
    unsigned GetNewGroundLevel(unsigned x, std::shared_ptr<LevelEntity> ground);

    /**
      *   @brief Remove specific type entities from level_entities
      *   @details Used to remove previously placed friendly planes (1 allowed at the time)
      *   @param entity_type LevelEntity type which are removed
      *   @param not_removed LevelEntity which isn't removed
      */
    void RemoveSpecificEntities(int entity_type, std::shared_ptr<LevelEntity> not_removed);

    /**
      *   @brief Convert string to LevelEntity type
      *   @remark This isn't currenly compatible with ResourceManager.
      *   On error case returns NO_ENTITY int value
      *   @param str Input string which is converted
      */
    int ConvertStrToType(std::string &str);

    /*  Variables */
    float level_y_limit = 0; /**< Tells level y limit (i.e. the lowest allowed point to place entities) */
    std::shared_ptr<LevelEntity> current_entity;
    float current_entity_height = 0;
    std::vector<std::shared_ptr<LevelEntity>> level_entities; /**< All LevelEntities */
    std::vector<std::shared_ptr<LevelEntity>> grounds; /**< All ground entities are also added here */
    std::map <unsigned, unsigned> ground_level; /**< Stores the ground level below */
    ResourceManager manager;

};

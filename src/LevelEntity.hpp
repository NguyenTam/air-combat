/**
  *   @file LevelEntity.hpp
  *   @brief Header for class LevelEntity
  */

#pragma once

/*  Includes  */

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <string>
#include <iostream>
#include <ostream>


/**
  *   @class LevelEntity
  *   @brief Class representing objects placed on Level during editing with
  *   LevelEditor
  *   @details Inherits sf::Drawable to be able to draw sprites
  */

class LevelEntity: public sf::Drawable
{
  public:

    /**
      *   @brief Empty constructor for LevelEntity
      *   @remark Constructs LevelEntity to position 0, 0 and with
      *   width, height 0
      */
    LevelEntity();

    /**
      *   @brief Standard constructor for LevelEntity
      *   @param x x coordinate
      *   @param y y coordinate
      *   @param width LevelEntity width
      *   @param height LevelEntity height
      *   @param image_path img_path, path to image representing the entity
      *   @param type LevelEntity type, defined in Level.hpp
      */
    LevelEntity(float x, float y, float width, float height, std::string image_path, int type = 0);

    /**
      *   @brief Copy constructor
      */
    LevelEntity(const LevelEntity &level_entity);

    /**
      *   @brief assignment operator
      */
    LevelEntity& operator=(const LevelEntity &level_entity);

    /**
      *   @brief Print overload as friend
      *   @remark Only for testing use
      */
    friend std::ostream& operator<<(std::ostream &os, const LevelEntity &level_entity);

    /**
      *   @brief Set new position for LevelEntity
      *   @param x New x coordinate
      *   @param y New y coordinate
      */
    void setPosition(float x, float y);

    /**
      *   @brief Set new position for LevelEntity
      *   @param position New position for LevelEntity
      */
    void setPosition(sf::Vector2f position);

    /**
      *   @brief Get LevelEntity position
      *   @return Return const reference to the position
      */
    const sf::Vector2f& getPosition();

    /**
      *   @brief Check whether position is inside or outside the entity
      *   @param x x coordinate to test
      *   @param y y coordinate to test
      *   @return Returns true if inside
      */
    bool isInside(float x, float y);

    /**
      *   @brief Set LevelEntity positioned true / false
      *   @param positioned New positioned value
      */
    void setPositioned(bool positioned);

    /**
      *   @brief Get positioned value
      *   @return Returns positioned
      */
    bool getPositioned();

    /**
      *   @brief Get LevelEntity type
      *   @return Returns type
      *   @remark Different types defined in Level.hpp
      */
    int getType();

    /**
      *   @brief Flip LevelEntity around y-axis
      */
    void flipLevelEntity();

    /**
      *   @brief Get LevelEntity width
      *   @return Returns width
      */
    float getWidth();
    /**
      *   @brief Get LevelEntity height
      *   @return Returns height
      */
    float getHeight();

    /**
      *   @brief Get LevelEntity orientation
      *   @return Returns 1 if flipped == false, otherwise returns 0
      */
    int getOrientation();

    /**
      *   @brief Set stretchable / unstretchable
      *   @param enable true-> stretchable
      */
    void setStretchable(bool enable);

    /**
      *   @brief Get stretchable
      *   @return Returns stretchable
      */
    bool getStretchable();

    /**
      *   @brief Set LevelEntity fully_constructed
      */
    void setFullyConstructed();

    /**
      *   @brief Get LevelEntity fully_constructed
      *   @return Returns fully_constructed
      */
    bool getFullyConstructed();

    /**
      *   @brief Try to activate LevelEntity stretching
      *   @param x Level x coordinate
      *   @param y Level y coordinate
      */
    void activateStretching(float x, float y);

    /**
      *   @brief Stretch LevelEntity
      *   @param float x Level x coordinate
      *   @param float y Level y coordinate
      *   @remark Does nothing if LevelEntity isn't stretchable
      */
    void stretch(float x, float y);

    /**
      *   @brief Set LevelEntity flippable to false
      *   @remark Call this when creating GROUND LevelEntity
      */
    void setNonFlippable();

    /**
      *   @brief Get LevelEntity left corner x coordinate
      *   @return Returns x
      */
    float getX();

    /**
      *   @brief Get LevelEntity top corner y coordinate
      *   @return Returns y
      */
    float getY();


  protected:
    /**
      *   @brief Draw LevelEntity
      *   @remark draw defined as pure virtual in sf::Drawable
      *   @param target Drawable window
      *   @param states RenderStates
      */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  private:

    /**
      *   @brief Load texture and create sprite
      *   @remark If texture can't be loaded, en empty sprite is created. Also,
      *   the created sprite is possible cut to match rect
      */
    void CreateSprite();

    /**
      *   @brief Store original values for x, y, width and height
      */
    void StoreOriginalValues();

    /*  Variables */

    float x; /**< Left corner */
    float y; /**< Top corner */
    float width;
    float height;
    float orig_x; // Original values
    float orig_y;
    float orig_width;
    float orig_height;
    sf::Vector2f position;
    sf::Rect<float> rect;
    bool positioned = false;
    int type = 0; /**< LevelEntity type, defined in Level.hpp */

    std::string img_path;
    sf::Texture texture;
    sf::Sprite sprite;
    bool flipped = false;
    bool stretchable = false; /**< Used with Ground */
    bool fully_constructed = false; /**< Used with Ground */
    bool flippable = true;


};

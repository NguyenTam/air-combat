/**
  *   @file image_button.hpp
  *   @brief Header for class ImageButton
  */

#pragma once

#include "button.hpp"


/*  Macros */
#define STD_IMAGE_PATH "../data/img/std_button.png"

/**
  *   @class ImageButton
  *   @brief Button inherited class which implements images as buttons
  */

class ImageButton: public Button
{
  public:

    /**
      *   @brief empty constructor for ImageButton
      *   @details Does Does all inits that are needed to crate a valid ImageButton
      */
    ImageButton();

    /**
      *   @brief Constructor for ImageButton
      *   @details Calls also basic button constructor
      *   @param button_name Name which is shown when Imagebutton is active
      *   @param img_path Valid path to image file
      *   @width Button (image) width
      *   @height Button (image) height
      *   @remark Make sure img_path is a valid path. width and height
      *   define how big partion of the image is visible (probably want to match
      *   those to image pixel size)
      */
    ImageButton(std::string button_name, std::string img_path, unsigned width, unsigned height);

    /**
      *   @brief Copy constructor
      */
    ImageButton(const ImageButton& button);

    /**
      *   @brief Assignment operator
      */
     ImageButton& operator=(const ImageButton& button);

    /**
      *   @brif Set ImageButton position
      *   @details Reimplemented from the base class Button::setPosition
      *   @param new_pos Position vector
      *   @remark Position must be set just after constructor
      */
    virtual void setPosition(sf::Vector2f new_pos);

    /**
      *   @brif Set ImageButton position
      *   @details Reimplemented from the base class Button::setPosition
      *   @param x x coordinate (the left most point)
      *   @param y y coordinate (the top coordinate)
      *   @remark Position must be set just after constructor
      */
    virtual void setPosition(float x, float y);

    /**
      *   @brief Activate/deactivate button
      *   @details Reimplemented from the base class method Button::tryActivate
      *   @param x Mouse x coordinate
      *   @param y Mouse y coordinate
      */
    virtual bool tryActivate(float x, float y);

    /**
      *   @details Activate/deactivate button
      *   @param activate true button activated, false deactivated
      *   @remark Reimplemented from the base class Button::activate
      */
    virtual void activate(bool activate);

    /**
      *   @brief Possibly sets button checked and calls click_action
      *   @details If coordinates match button frame and button isn't checked,
      *   click_action called
      *   @param x Mouse x coordinate
      *   @param y Mouse y coordinate
      *   @return Returns true if ImageButton was clicked
      *   @remark Reimplemented from the base class Button::checkClicked
      */
    virtual bool checkClicked(float x, float y);

    /**
      *   @brief Set button checked and call click_action
      *   @remark Reimplemented from the base class Button::clickAction
      */
    virtual void clickAction();

    /**
      *   @brief Set higlight color used when button is checked
      *   @details Assigns color to checked_color
      *   @param color New highlight color
      */
    void setHighlightColor(sf::Color color);

    /**
      *   @brief Set ImageButton unchecked
      */
    void setUnchecked();

  protected:
    /**
      *   @brief Draw ImageButton to window
      *   @details Inherited from Button and sf::Drawable
      *   @param target RenderTarget window where button is drawn
      *   @param states window dependend parameters
      */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    /**
      *   @brief Set correct text position
      *   @remark Reimplemented from the base class Button::SetTextPosition
      *   @details Positions text directly under ImageButton
      */
    virtual void SetTextPosition();

  private:
    /**
      *   @brief Set correct image position
      */
    void SetImagePosition();

    /**
      *   @brief Do basic ImageButton constructor work
      */

    void ConstructImageButton();


    /*  Variables */
    sf::Sprite image_sprite;
    sf::Texture image_texture;
    sf::RectangleShape checked_rect; /**< This shape is draw when button is checked */
    sf::Color checked_color; /**< Highlight color used when button is checked */
    unsigned text_size = 10;
    bool active = false;
    bool checked = false;
    std::string image_path;
};

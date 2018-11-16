/**
  *   @file button.hpp
  *   @brief Header for Button class
  */

#pragma once

/*  Includes */

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <string>
#include <iostream>
#include <functional>



/*  Macros  */

/**
  *   @brief Macro to arial font location
  */
#define FONT_ARIAL "../data/fonts/arial.ttf"

/**
  *   @brief Macro to Courier font location
  */
#define FONT_COURIER "../data/fonts/Courier.ttf"

/**
  *   @brief Macro which tells how much space (pixels) is left between text
  *   and button_rect in x dimension
  */
#define BUTTON_FREE_SPACE_X 30

/**
  *   @brief Macro which tells how much space (pixels) is left between text
  *   and button_rect in y dimension
  */
#define BUTTON_FREE_SPACE_Y 20



/**
  *   @class Button
  *   @brief Button class used in UI
  *   @details Inherits sf::Drawable to draw objects to RenderTarget via pure
  *   virtual draw method.
  *   @remark To create nice equally sized buttons which texts are centered,
  *   create first the button with longest name with standard constructor. Then
  *   use getWidth() and getHeight() to get the size of the button. Pass these
  *   values to the alternative constructor. Now the newly created button should
  *   have same size as the first one
  */

class Button: public sf::Drawable
{
  public:


    /**
      *   @brief Standard constructor for Button
      *   @param button_name Button name
      *   @param color The normal color of Button
      *   @details Creates Button using Courier as font and font size is font_size
      *   @remark By default active_color is set to color, call setActiveColor to set it
      */
      Button(std::string button_name, sf::Color color);



    /**
      *   @brief Alternative constructor for Button
      *   @param button_name Button name
      *   @param color The normal color of Button
      *   @param width Button width
      *   @param height Button height
      *   @details Creates Button using Courier as font and font size is font_size
      *   @remark Use this to after creating the button with longest text
      *   @remark By default active_color is set to color, call setActiveColor to set it
      */
      Button(std::string button_name, sf::Color color, unsigned width, unsigned height);

    /**
      *   @brief Set outside class function as click_action
      *   @details Used to bind to UI button press specific function
      *   @param function std::bind function
      *   @remark This needs to be set directly after button is created
      */

      void setClickFunction(std::function<void()> const &function);

    /**
      *   @brief Set position for Button
      *   @param new_pos Button new position as Vector2f
      */
      virtual void setPosition(sf::Vector2f new_pos);

    /**
      *   @brief Set Position for Button
      *   @param x x coordinate
      *   @param y y coordinate
      */
      virtual void setPosition(float x, float y);

    /**
      *   @brief Get Button position
      *   @return Returns Button position
      */
      sf::Vector2f getPosition();

    /**
      *   @brief Get Button text
      *   @return Returns text
      */
      sf::Text getText();

    /**
      *   @brief Get Button width
      *   @return Returns width
      */
      unsigned getWidth();

      /**
        *   @brief Get Button height
        *   @return Returns height
        */
      unsigned getHeight();

      /**
        *   @brief Check if button is clicked
        *   @param x Mouse x coordinate
        *   @param y Mouse y coordinate
        *   @return Returns true if Button was clicked
        *   @details If button is clicked calls click_action
        *   @remark Make sure click_action has been set. This method can be
        *   reimplemented in lower classes
        */

      virtual bool checkClicked(float x, float y);

      /**
        *   @brief Call click_action
        *   @remark click action must have been set. This method can be
        *   reimplemented in lower classes
        */
      virtual void clickAction();

      /**
        *   @brief Try to activate button
        *   @param x Mouse x coordinate
        *   @param y Mouse y coordinate
        *   @return Returns true if a Button was activated
        *   @details Activates button if x and y match to button frame,
        *   orherwise button is deactivated
        *   @remark Can be reimplemented in lower classes
        */
      virtual bool tryActivate(float x, float y);

      /**
        *   @brief Activate Button
        *   @param activate if true, activate, else deactivate
        *   @remark Can be reimplemented in lower classes
        */
      virtual void activate(bool activate);

      /**
        *   @brief Set active_color
        *   @param color New active_color
        *   @remark By default active color is same as normal_color
        */
      void setActiveColor(sf::Color color);

  protected:

    /**
      *   @brief Called from constructor to do basic set up work
      *   @param color color passed from constructor
      */

      void SetUp(sf::Color color);

    /**
      *   @brief Implementation of draw method
      *   @remark defined as pure virtual in sf::Drawable
      */

      virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    /**
      *   @brief Try to position text correctly
      *   @details Goal is to center the text within the frame rectangle
      *   @remark Works only with Courier (monospace font)
      */
      virtual void SetTextPosition();


    /*  Variables */

    std::string name;
    sf::Vector2f position;
    unsigned width;
    unsigned height;
    sf::Text text;
    sf::Font font;
    sf::Color normal_color; /**< Color when button isn't active */
    sf::Color active_color; /**< Color when button is active (hover on) */
    unsigned font_size = 20;
    sf::Rect<float> frame; /**< Button frame rect */
    sf::RectangleShape button_rect; /**< Draws button rectangle frames */
    std::function<void ()> click_action; /*z UI class function */

  private:

    /**
      *   @brief Calculate correct size for the button
      *   @details Uses name char amount and font size to calculate and set
      *   correct width & height values
      *   @remark name needs to be initialized prior calling this method
      */
    void CalculateSize();




};

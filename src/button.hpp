/**
  *   @file button.hpp
  *   @brief Header for Button class
  */

#pragma once

/* To get rid of sf::setColor deprecated warnings uncomment:
#define SFML_NO_DEPRECATED_WARNINGS */

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
  *   have same size as the first one. After creating a Button call setPosition
  *   to set correct position for the Button.
  */

class Button: public sf::Drawable
{
  public:

    /**
      *   @brief Empty constructor for Button
      *   @details Does all inits that are needed to crate a valid Button
      */
      Button();

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
      *   @remark By default Buttons are created uncheckable, call setCheckable(true)
      *   to set Button checkable
      */
      Button(std::string button_name, sf::Color color, unsigned width, unsigned height);

      /**
        *   Copy constructor
        */
      Button(const Button& button);

      /**
        *   @brief Assignment operator
        *   @remark Does not assign button status
        */
      Button& operator=(const Button& button);

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
      sf::Text& getText();

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

      /**
        *   @brief Set Button text color
        *   @param color New text color
        */
      void setTextColor(sf::Color color);

      /**
        *   @brief Set outline for Button
        *   @param thickness Outline thickness (recommended <= 1.0)
        *   @param color Outline color
        */
      void setOutline(float thickness, sf::Color color);

      /**
        *   @brief Set text style
        *   @param style Text style (e.g. sf::Text::Regular)
        *   @param font_size New font_size
        *   @param text_color New text color
        */
      void setTextStyle(unsigned style, unsigned font_size, sf::Color text_color);

      /**
        *   @brief Set Button enabled value
        *   @param enable true -> enable, false -> disable
        */
      void setEnabled(bool enable);

      /**
        *   @brief Set Button (ImageButton) checkable or uncheckable
        *   @param checkable true -> checkable, false -> uncheckable
        */
      void setCheckable(bool checkable);

      /**
        *   @brief Set Button unchecked
        *   @remark Can be reimplemented in lower classes
        */
      virtual void setUnchecked();
      /**
        *   @brief Set Button checked
        *   @remark Use carefully, incorrect usage may break button status
        */
      void setChecked();

      /**
        *   @brief Get checked value
        *   @return Returns checked
        */
      bool getChecked();

      /**
        *   @brief Make Button clickable or unclickable
        *   @param enable true-> clicking_enabled
        */
      void enableClicking(bool enable);

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
    std::function<void ()> click_action; /**< UI class function */
    bool enabled = true; /**< If false, Button isn't draw + it can'be clicked nor activated */
    bool checkable = false;
    sf::RectangleShape checked_rect; /**< This shape is draw when button is checked */
    sf::Color checked_color; /**< Highlight color used when button is checked */
    bool checked = false;
    bool clicking_enabled = true; /**< Button can be clicked */

  private:

    /**
      *   @brief Calculate correct size for the button
      *   @details Uses name char amount and font size to calculate and set
      *   correct width & height values
      *   @remark name needs to be initialized prior calling this method
      */
    void CalculateSize();




};

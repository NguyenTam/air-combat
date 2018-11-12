/**
  *   @file Button.hpp
  *   @brief Header for Button class
  */

#pragma once

/*  Includes */

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <string>
#include <iostream>



/*  Macros  */

/**
  *   @brief Macro to arial font location
  */
#define FONT_ARIAL "../data/fonts/arial.ttf"



/**
  *   @class Button
  *   @brief Button class used in UI
  *   @details Inherits sf::Drawable to draw objects to RenderTarget via pure
  *   virtual draw method
  */

class Button: public sf::Drawable
{
  public:

    /**
      *   @brief Constructor for Button
      *   @param button_name Button name
      *   @param color The normal color of Button
      *   @details Creates Button using Arial as font and font size is font_size
      */
      Button(std::string button_name, sf::Color color);

    /**
      *   @brief Set position for Button
      *   @param new_pos Button new position as Vector2f
      */
      void setPosition(sf::Vector2f new_pos);

    /**
      *   @brief Set Position for Button
      *   @param x x coordinate
      *   @param y y coordinate
      */
      void setPosition(float x, float y);

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

  protected:

    /**
      *   @brief Implementation of draw method
      *   @remark defined as pure virtual in sf::Drawable
      */

      virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


    /*  Variables */

    std::string name;
    sf::Vector2f position;
    unsigned width = 60;
    unsigned height = 60;
    sf::Text text;
    sf::Font font;
    sf::Color normal_color; /**< Color when button isn't active */
    sf::Color active_color; /**< Color when button is active (hover on) */
    unsigned font_size = 30;

  private:

};

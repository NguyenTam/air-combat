/**
  *   @file button.cpp
  *   @brief Contains class Button source
  */


#include "button.hpp"


/*  Class Button */


/*  Constructor */

Button::Button(std::string button_name, sf::Color color): sf::Drawable()
{
  // Assign name and color
  name = button_name;
  normal_color = color;

  // Create text
  if( !font.loadFromFile(FONT_ARIAL) )
  {
    // TODO error handling
  }
  text = sf::Text(name, font, font_size);
  text.setFillColor(sf::Color::Red);
  std::cout << "Hello" << std::endl;

}


/* Update Button position */

void Button::setPosition(sf::Vector2f new_pos)
{
  position = new_pos;
  float x = position.x;
  float y = position.y;

  // Correct text position
  text.setPosition(x + 15, y + 20);

}

/*  Update Button position */

void Button::setPosition(float x, float y)
{
  sf::Vector2f new_pos = sf::Vector2f(x, y);
  position = new_pos;

  // Correct text position
  text.setPosition(x +15, y +20);
}

/*  Get Button position */

sf::Vector2f Button::getPosition()
{
  return position;
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  std::cout << "Drawing" << std::endl;
  // Draw all components independently
  target.draw(text, states);
}


/*  Get text */

sf::Text Button::getText()
{
  return text;
}

/**
  *   @file button.cpp
  *   @brief Contains class Button source
  */


#include "button.hpp"


/*  Class Button */


/*  Standard constructor */

Button::Button(std::string button_name, sf::Color color): sf::Drawable()
{
  name = button_name;

  /* CalculateSize must be called prior using width and height and name
    must be initialized */
  CalculateSize();

  SetUp(color);
}

/*  Alternative constructor */

Button::Button(std::string button_name, sf::Color color, unsigned width, unsigned height)
: sf::Drawable()
{
  name = button_name;
  this->width = width;
  this->height = height;
  SetUp(color);

}

/*  Bind an UI function as click_action */

void Button::setClickFunction(std::function<void()> const &function)
{
  click_action = function;
}



/*  Set up Button */

void Button::SetUp(sf::Color color)
{

  normal_color = color;
  active_color = color; // default active_color == normal_color

  // Create text
  if( !font.loadFromFile(FONT_COURIER) )
  {
    // TODO error handling
  }
  text = sf::Text(name, font, font_size);
  text.setFillColor(sf::Color::Red);
  text.setStyle(sf::Text::Bold);

  // Set button_rect matching button
  button_rect.setSize(sf::Vector2f(width, height));
  button_rect.setFillColor(normal_color);

}


/* Update Button position */

void Button::setPosition(sf::Vector2f new_pos)
{
  position = new_pos;
  float x = position.x;
  float y = position.y;

  // Set frame
  frame = sf::Rect<float>(x, y, width, height);
  // Set button_rect
  button_rect.setPosition(position);

  // Correct text position
  SetTextPosition();

}

/*  Update Button position */

void Button::setPosition(float x, float y)
{
  sf::Vector2f new_pos = sf::Vector2f(x, y);
  position = new_pos;

  // Set frame
  frame = sf::Rect<float>(x, y, width, height);

  // Set button_rect
  button_rect.setPosition(position);

  // Correct text position
  SetTextPosition();
}

/*  Get Button position */

sf::Vector2f Button::getPosition()
{
  return position;
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  // Draw all components independently
  target.draw(button_rect, states);
  target.draw(text, states);

}


/*  Get text */

sf::Text Button::getText()
{
  return text;
}


/* Try to set correct text position */

void Button::SetTextPosition()
{
  // y
  float correct_y = (height / 2) - font_size / 2;

  float correct_x;
  unsigned chars = name.length();
  if (chars % 2 == 0)
  {
    correct_x = 0.5 * width - (chars / 2) * 0.6 * font_size;

  }
  else
  {
    correct_x = 0.5 * width - (chars / 2 * font_size + 0.3 * font_size)  * 0.6 * font_size;
  }

  text.setPosition(correct_x + position.x, correct_y + position.y);

}

/* Set correct width and height */

void Button::CalculateSize()
{
  // text must be initialized
  unsigned chars = name.length();
  // approximation
  width = 2 * BUTTON_FREE_SPACE_X + chars * (font_size / 2);

  height = 2 * BUTTON_FREE_SPACE_Y + font_size;

}

/*  Get width */
unsigned Button::getWidth()
{
  return width;
}

/* Get height */
unsigned Button::getHeight()
{
  return height;
}


/*  Check if object has been clicked and possibly call click_action */

bool Button::checkClicked(float x, float y)
{
  if (frame.contains(x, y))
  {
    click_action();
    return true;
  }
  return false;
}

/* Call click_action */

void Button::clickAction()
{
  click_action();
}


/* Activate/deactivate Button */

bool Button::tryActivate(float x, float y)
{

  if (frame.contains(x, y))
  {
    button_rect.setFillColor(active_color);
    return true;
  }
  else
  {
    button_rect.setFillColor(normal_color);
    return false;
  }

}

/* Activate/deactivate */
void Button::activate(bool activate)
{
  if (activate)
  {
    button_rect.setFillColor(active_color);
  }
  else
  {
    button_rect.setFillColor(normal_color);
  }

}

/*  Set active_color */

void Button::setActiveColor(sf::Color color)
{
  active_color = color;
}

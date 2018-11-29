/**
  *   @file button.cpp
  *   @brief Contains class Button source
  */


#include "button.hpp"


/*  Class Button */


/*  Empty constructor */

Button::Button(): sf::Drawable()
{
  name = "Button";

  /* CalculateSize must be called prior using width and height and name
    must be initialized */
  CalculateSize();

  SetUp(sf::Color::White);
  // Init some position
  setPosition(sf::Vector2f(0, 0));
}


/*  Standard constructor */

Button::Button(std::string button_name, sf::Color color): sf::Drawable()
{
  name = button_name;

  /* CalculateSize must be called prior using width and height and name
    must be initialized */
  CalculateSize();

  SetUp(color);
  // Init some position
  setPosition(sf::Vector2f(0, 0));
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

/* Copy constructor */

Button::Button(const Button& button): sf::Drawable()
{
  name = button.name;
  width = button.width;
  height = button.height;
  normal_color = button.normal_color;
  SetUp(normal_color);
  active_color = button.active_color;
  setPosition(button.position);

}


/* Copy assignment */

Button& Button::operator=(const Button& button)
{
  name = button.name;
  width = button.width;
  height = button.height;
  normal_color = button.normal_color;
  SetUp(normal_color);
  active_color = button.active_color;
  setPosition(button.position);

  return *this;
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
  text.setColor(sf::Color::Red);
  text.setStyle(sf::Text::Bold);

  // Set button_rect matching button
  button_rect.setSize(sf::Vector2f(width, height));
  button_rect.setFillColor(normal_color);

  // Create also own RectangleShape for checked mode
  checked_color = sf::Color(100, 100, 100, 80);
  checked_rect.setSize(sf::Vector2f(width, height));
  checked_rect.setFillColor(checked_color);
  checked_rect.setOutlineThickness(1);
  checked_rect.setOutlineColor(sf::Color::Black);

}


/* Update Button position */

void Button::setPosition(sf::Vector2f new_pos)
{
  position = new_pos;
  float x = position.x;
  float y = position.y;

  // Set frame
  frame = sf::Rect<float>(x, y, width, height);
  // Set button_rect and checked_rect positions
  button_rect.setPosition(position);
  checked_rect.setPosition(position);

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

  // Set button_rect and checked_rect positions
  button_rect.setPosition(position);
  checked_rect.setPosition(position);

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
  if (enabled && !checked)
  {
    // Draw all components independently
    target.draw(button_rect, states);
    target.draw(text, states);
  }
  else if (enabled)
  {
    target.draw(text, states);
    target.draw(checked_rect, states);
  }

}


/*  Get text */

sf::Text& Button::getText()
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
    correct_x = 0.5 * width - ((chars / 2) * font_size * 0.6 + 0.3 * font_size);
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
  if (enabled && clicking_enabled)
  {
    if (frame.contains(x, y))
    {
      if (! checked)
      {
        if (checkable)
        {
          checked = true;
        }
        click_action();
        return true;
      }

    }
  }
  return false;
}

/* Call click_action */

void Button::clickAction()
{
  if (! checked)
  {
    if (checkable)
    {
      checked = true;
    }

    click_action();
  }
}


/* Activate/deactivate Button */

bool Button::tryActivate(float x, float y)
{

  if (enabled && frame.contains(x, y))
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
  if (activate && enabled)
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

/* Set text color */
void Button::setTextColor(sf::Color color)
{
  text.setColor(color);
}

/* Set outline for Button */
void Button::setOutline(float thickness, sf::Color color)
{
  button_rect.setOutlineThickness(thickness);
  button_rect.setOutlineColor(color);
}


/*  Set text style */
void Button::setTextStyle(unsigned style, unsigned font_size, sf::Color text_color)
{
  this->font_size = font_size;
  text = sf::Text(name, font, font_size);
  text.setColor(text_color);
  text.setStyle(style);

  // Correct text position
  SetTextPosition();

}

/* Set Button enabled/disabled */
void Button::setEnabled(bool enable)
{
  enabled = enable;
}

/* Set checkable/uncheckable */
void Button::setCheckable(bool checkable)
{
  this->checkable = checkable;
}


/* Set unchecked */
void Button::setUnchecked()
{
  checked = false;
}

/* Set checked */
void Button::setChecked()
{
  checked = true;
}

/* Get checked */
bool Button::getChecked()
{
  return checked;
}

/*  Enable / disable clicking */
void Button::enableClicking(bool enable)
{
  clicking_enabled = enable;
}

/**
  *   @file TextInput.cpp
  *   @brief Source for class TextInput
  */

#include "TextInput.hpp"


/*  Class TextInput */


/*  Empty constructor */
TextInput::TextInput(): sf::Drawable()
{
  width = 0;
  height = 0;
  x = 0;
  y = 0;
  sf::Color text_color = sf::Color::Black;
  input = "";
  font.loadFromFile("../data/fonts/Courier.ttf");
  text = sf::Text(input, font, font_size);
  text.setColor(text_color);
  active_color = sf::Color(200, 200, 200);
  std_color = sf::Color::White;
  CreateSanitizationSet();
  CreateTextInput();
}


/*  Standard constructor */
TextInput::TextInput(float x, float y, float width, float height): sf::Drawable()
{
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
  sf::Color text_color = sf::Color::Black;
  input = "";
  font.loadFromFile("../data/fonts/Courier.ttf");
  text = sf::Text(input, font, font_size);
  text.setColor(text_color);
  text.setPosition(x, y);
  frame.setOutlineColor(sf::Color::Black);
  active_color = sf::Color(200, 200, 200);
  std_color = sf::Color::White;

  CreateSanitizationSet();
  CreateTextInput();
}

/* Copy constructor */
TextInput::TextInput(const TextInput &text_input)
{
  x = text_input.x;
  y = text_input.y;
  width = text_input.width;
  height = text_input.height;
  font = text_input.font;
  font_size = text_input.font_size;
  input = text_input.input;
  line = text_input.line;
  CreateTextInput();
  // Copy chars_on_lines
  int i = 0;
  // This will cause problems if input is partially empty
  for (auto it = text_input.chars_on_lines.begin(); it != text_input.chars_on_lines.end(); it++)
  {
    chars_on_lines[i] = *it;
    i++;
  }
  text_color = text_input.text_color;
  text = sf::Text(input, font, font_size);
  text.setColor(text_color);
  active_color = text_input.active_color;
  std_color = text_input.std_color;
  highlight = sf::RectangleShape(sf::Vector2f(0.6 * (float) font_size, font_size));
  CreateSanitizationSet();
}

/*  Assignment overload */
TextInput& TextInput::operator=(const TextInput &text_input)
{
  x = text_input.x;
  y = text_input.y;
  width = text_input.width;
  height = text_input.height;
  font = text_input.font;
  font_size = text_input.font_size;
  input = text_input.input;
  line = text_input.line;
  CreateTextInput();
  // Copy chars_on_lines
  int i = 0;
  // This will cause problems if input is partially empty
  for (auto it = text_input.chars_on_lines.begin(); it != text_input.chars_on_lines.end(); it ++)
  {
    chars_on_lines[i] = *it;
    i++;
  }
  text_color = text_input.text_color;
  text = sf::Text(input, font, font_size);
  text.setColor(text_color);
  text.setPosition(x, y);
  active_color = text_input.active_color;
  std_color = text_input.std_color;

  return *this;
}

/*  Set position */
void TextInput::setPosition(float x, float y)
{
  this->x = x;
  this->y = y;
  rect = sf::Rect<float>(x, y, width, height);
  frame.setPosition(x, y);
  text.setPosition(x, y);
}

/*  Draw TextInput */
void TextInput::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(frame, states);
  if (active && highlight_on && higlight_color)
  {
    target.draw(highlight, states);
  }
  target.draw(text, states);
}

/*  Activate / deactivate */
bool TextInput::tryActivate(float x, float y)
{
  if (rect.contains(x, y))
  {
    if (active)
    {
      // deactivate
      active = false;
      frame.setFillColor(std_color);

    }
    else
    {
      // activate
      active = true;
      frame.setFillColor(active_color);
      return true;
    }
  }
  return false;
}

/*  Add char to input */
void TextInput::addChar(char32_t new_char)
{
  if (active)
  {
    if (new_char < 128)
    {
      // Only ascii allowed
      // Sanitise
      bool ok = false;
      if (strict_sanitization)
      {
        auto it = input_sanitization_strict.find(new_char);
        if (it == input_sanitization_strict.end())
        {
          ok = true;
        }
      }
      else
      {
        auto it = input_sanitization.find(new_char);
        if (it == input_sanitization.end())
        {
          ok = true;
        }
      }
      if (ok)
      {
        // Uset input ok
        if (new_char == 8)
        {
          // BackSpace
          removeChar();
        }
        // Notice: following works only for Courier font
        else if ((0.575 * font_size * (float)(chars_on_lines[line -1] + 1)) < width)
        {
          // Add the char to current line
          input += new_char;
          text.setString(input);
          chars_on_lines[line -1] += 1; // Add one char to correct line
        }
        else if (line < (int) (height - font_size) / font.getLineSpacing(font_size))
        {
          // Move to the next line
          line ++;
          input += '\n';
          input += new_char;
          text.setString(input);
          chars_on_lines[line -1] += 1;
        }
      }

    }
    HighlightCurrent();
  }

}

/*  Activate */
void TextInput::activate()
{
  active = true;
  frame.setFillColor(active_color);
}

/*  Deactivate */
void TextInput::deactivate()
{
  active = false;
  frame.setFillColor(std_color);
}

/*  Set outline */
void TextInput::setOutline(sf::Color color, float thickness)
{
  frame.setOutlineColor(color);
  frame.setOutlineThickness(thickness);
}

/*  Set text_color */
void TextInput::setTextColor(sf::Color color)
{
  text_color = color;
  text.setColor(text_color);
}


/*  Remove previous char */
void TextInput::removeChar()
{
  if (chars_on_lines[line -1] > 0)
  {
    input.pop_back();
    chars_on_lines[line -1] -= 1;
  }
  else if (input.length() >= 2)
  {
    // Remove line feed also
    input.pop_back();
    input.pop_back();
    line --;
    chars_on_lines[line -1] -= 1;
  }
  text.setString(input);

}

/*  Higlight current char */
void TextInput::HighlightCurrent()
{

  if ((chars_on_lines[line -1] + 1) * 0.575 * (float) font_size < width)
  {
    // Cursor still not in the corner
    highlight.setPosition(x + (float) (chars_on_lines[line -1] ) * font_size * 0.575,
                            y + ((line - 1) * font.getLineSpacing(font_size)) + font_size / 4);
    highlight_on = true;
  }
  else if (line < max_lines)
  {
    // Line change needed
    highlight.setPosition(x, y + (line * font.getLineSpacing(font_size)) + font_size / 4);
    highlight_on = true;
  }
  else
  {
    // highlight would be outside the box
    highlight_on = false;
  }

}


/*  Create input_sanitization */
void TextInput::CreateSanitizationSet()
{
  // Set contains integer values for ascii chars which should be sanitized
  input_sanitization = {0, 1, 2, 3, 4, 5, 6, 7, 9, 10, 11, 12, 13, 14, 15, 16, 17,
  18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 34, 47, 91, 92, 93, 127};
  // Strict input sanitization set for filenames
  input_sanitization_strict = {0, 1, 2, 3, 4, 5, 6, 7, 9, 10, 11, 12, 13, 14, 15,
  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
  36, 37,38, 39, 40, 41, 42, 43, 44, 46, 47, 58, 59, 60, 61, 62, 63, 64, 91, 92,
  93, 94, 96, 123, 124, 125, 126, 127};
}


/* Enable / disable strict_sanitization */
void TextInput::enableStrictSanitization(bool activate)
{
  strict_sanitization = activate;
}

/*  Do basic initializations */
void TextInput::CreateTextInput()
{
  rect = sf::Rect<float>(x, y, width, height);
  frame = sf::RectangleShape(sf::Vector2f(width, height));
  frame.setPosition(x, y);

  highlight = sf::RectangleShape(sf::Vector2f(0.575 * (float) font_size, font_size));
  highlight.setPosition(x, y + font_size / 4);
  highlight.setFillColor(sf::Color(50, 50, 50, 50));

  // Create chars_on_lines vector
  if (chars_on_lines.size())
  {
    chars_on_lines.clear();
  }
  int i = 0;
  while (i < (int) (height - font_size) / font.getLineSpacing(font_size))
  {
    chars_on_lines.push_back(0);
    i ++;
  }
  // assign value to max_lines variable, note different indexing
  max_lines = i;
}

/*  Get input text */
std::string TextInput::getInputText()
{
  return input;
}

/*  Create highlight effect */
void TextInput::highlightEffect()
{
  // higlight_color is used to create highlight effect
  if (cycles == 4000)
  {
    if (higlight_color)
    {
      higlight_color = false;
    }
    else
    {
      higlight_color = true;
    }
    cycles = 0;
  }
  cycles ++;
}

/*  Set new input text */
void TextInput::setText(std::string text)
{
  // Correct chars_on_lines
  if (max_lines > 0)
  {
    line = 1; //This needs to be inited
    for (int i = 0; i < max_lines; i++)
    {
      // Reset chars_on_lines
      chars_on_lines[i] = 0;
    }
    // Create chars_on_lines based on the text
    for (auto it = text.begin(); it != text.end(); it++)
    {
      if (*it == '\n')
      {
        // Go to next line and reset chars on that line
        line ++;
        if (line >= max_lines)
        {
          // String too long, erase the end of it
          text.erase(it, text.end());
          break;
        }
      }
      else
      {
        // Correct char amount on lines
        chars_on_lines[line -1] += 1;
      }
    }

    // Set string
    input = text;
    this->text.setString(input);
  }
  HighlightCurrent();
}

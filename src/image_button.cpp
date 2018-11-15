/**
  *   @file image_button.cpp
  *   @brief Contains class ImageButton source
  */


#include "image_button.hpp"




/* Constructor for ImageButton */
ImageButton::ImageButton(std::string button_name, std::string img_path, unsigned width, unsigned height)
: Button(button_name, sf::Color::Transparent, width, height)
{
  // Set correct text style and font size
  text.setStyle(sf::Text::Regular);
  text.setCharacterSize(text_size);
  // Set correct outline style for ImageButton
  button_rect.setOutlineThickness(2);
  button_rect.setOutlineColor(sf::Color::Black);
  // Create also own RectangleShape for checked mode
  checked_color = sf::Color(100, 100, 100, 100);
  checked_rect.setFillColor(checked_color);
  checked_rect.setOutlineThickness(2);
  checked_rect.setOutlineColor(sf::Color::Black);


  if (! image_texture.loadFromFile(img_path))
  {
    // use some standard image

  }
  // Construct image_sprite
  image_sprite.setTexture(image_texture);

}


/*  Set ImageButton position from Vector2f */
void ImageButton::setPosition(sf::Vector2f new_pos)
{
  position = new_pos;
  float x = position.x;
  float y = position.y;

  // Set frame
  frame = sf::Rect<float>(x, y, width, height);
  // Set button_rect
  button_rect.setPosition(position);
  checked_rect.setPosition(position);
  // If texture is bigger than size it's visible only partially
  image_sprite.setTextureRect(sf::Rect<int>(0, 0, (int) width, (int) height));

  SetImagePosition();
  SetTextPosition();
}


/*  Set ImageButton position from coordinates */
void ImageButton::setPosition(float x, float y)
{
  sf::Vector2f new_pos = sf::Vector2f(x, y);
  position = new_pos;

  // Set frame
  frame = sf::Rect<float>(x, y, width, height);

  // Set button_rect
  button_rect.setPosition(position);
  checked_rect.setPosition(position);

  SetImagePosition();
  SetTextPosition();
}

/* Set correct image_sprite position */
void ImageButton::SetImagePosition()
{
  image_sprite.setPosition(position.x, position.y);
}


/*  Draw correct objects */
void ImageButton::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  // draw the sprite
  target.draw(image_sprite, states);
  if (checked)
  {
    target.draw(checked_rect, states);
  }
  else if(active)
  {
    // draw button_rect outline
    target.draw(button_rect, states);
    // draw text
    target.draw(text, states);
  }
}

/*  Activate button if coordinates match */
bool ImageButton::tryActivate(float x, float y)
{
  if (frame.contains(x, y))
  {
    active = true;
    return true;
  }
  else
  {
    active = false;
    return false;
  }
}

/*  Activate/deactivate button */
void ImageButton::activate(bool activate)
{
  if (activate)
  {
    active = true;
  }
  else
  {
    active = false;
  }

}

/* Set text below button and centered in x dimension */
void ImageButton::SetTextPosition()
{
  float x = position.x + (float) width / 2;
  float y = position.y + (float) height;
  text.setPosition(x, y);
}


/* Click button if coordinates match and button isn't checked */
bool ImageButton::checkClicked(float x, float y)
{
  if (frame.contains(x,y))
  {
    // Set correct status
    active = false;
    if (checked)
    {
      checked = false;
    }
    else
    {
      checked = true;
      // Call click_action
      click_action();
      return true;
    }
  }
  return false;

}

/*  Set correct button status after clicking */
void ImageButton::clickAction()
{
  active = false;
  if (checked)
  {
    checked = false;
  }
  else
  {
    checked = true;
    click_action();
  }

}

/*  Set new higlight color */
void ImageButton::setHighlightColor(sf::Color color)
{
  checked_color = color;
  checked_rect.setFillColor(checked_color);

}

/**
  *   @file image_button.cpp
  *   @brief Contains class ImageButton source
  */


#include "image_button.hpp"


/* Empty constructor */

ImageButton::ImageButton(): Button("ImageButton", sf::Color::Transparent, 50, 50)
{
  checkable = true;
  image_path = STD_IMAGE_PATH;
  ConstructImageButton();
  setPosition(0, 0);
}


/* Constructor for ImageButton */
ImageButton::ImageButton(std::string button_name, std::string img_path, unsigned width, unsigned height)
: Button(button_name, sf::Color::Transparent, width, height)
{
  checkable = true;
  image_path = img_path;
  ConstructImageButton();
  setPosition(0, 0);
}


/* Basic ImageButton construction */

void ImageButton::ConstructImageButton()
{
  // Set correct text style and font size
  text.setStyle(sf::Text::Regular);
  text.setColor(sf::Color::Black);
  text.setCharacterSize(text_size);
  // Set correct outline style for ImageButton
  button_rect.setOutlineThickness(1);
  button_rect.setOutlineColor(sf::Color::Black);

  if (! image_texture.loadFromFile(image_path))
  {
    // use some standard image
    image_texture.loadFromFile(STD_IMAGE_PATH);

  }
  // Construct image_sprite, cut image from top left if its bigger than the button
  image_sprite = sf::Sprite(image_texture, sf::IntRect(0, 0, width, height));
}

/* Copy constructor */

ImageButton::ImageButton(const ImageButton& button):
Button("ImageButton", sf::Color::Transparent, 50, 50)
{
  checkable = true;
  name = button.name;
  width = button.width;
  height = button.height;
  normal_color = button.normal_color;
  image_path = button.image_path;

  // Basic construction
  SetUp(normal_color);
  setPosition(button.position);
  ConstructImageButton();
  checked_color = button.checked_color;
}


/* Copy assignment */

ImageButton& ImageButton::operator=(const ImageButton& button)
{
  name = button.name;
  width = button.width;
  height = button.height;
  normal_color = button.normal_color;
  image_path = button.image_path;

  // Basic construction
  SetUp(normal_color);
  setPosition(button.position);
  ConstructImageButton();
  checked_color = button.checked_color;


  return *this;
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
  if (enabled)
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

}

/*  Activate button if coordinates match */
bool ImageButton::tryActivate(float x, float y)
{
  if (enabled && frame.contains(x, y))
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
  if (activate && enabled)
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
  float x = position.x;//+ (float) width / 2;
  float y = position.y + (float) height;
  text.setPosition(x, y);
}


/* Click button if coordinates match and button isn't checked */
bool ImageButton::checkClicked(float x, float y)
{
  if (enabled)
  {
    if (frame.contains(x,y))
    {
      // Set correct status
      active = false;
      if (checked)
      {
        checked = false;
        return true;
      }
      else
      {
        if (checkable)
        {
          checked = true;
        }

        // Call click_action
        click_action();
        return true;
      }
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
    if (checkable)
    {
      checked = true;
    }

    click_action();
  }

}

/*  Set new higlight color */
void ImageButton::setHighlightColor(sf::Color color)
{
  checked_color = color;
  checked_rect.setFillColor(checked_color);

}

/*  Uncheck ImageButton */
void ImageButton::setUnchecked()
{
  checked = false;
  active = false;
}

/* Scale ImageButton */
void ImageButton::setScale(float scale)
{

  float tmp_width = (float) width * scale;
  float tmp_height = (float) height * scale;
  width = (unsigned) tmp_width;
  height = (unsigned) tmp_height;
  button_rect.setSize(sf::Vector2f(width, height));
  checked_rect.setSize(sf::Vector2f(width, height));

  // Scale also the sprite
  image_sprite.setScale(scale, scale);
}

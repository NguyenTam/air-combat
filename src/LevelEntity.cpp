/**
  *   @file LevelEntity.cpp
  *   @brief Source code for class LevelEntity
  */

#include "LevelEntity.hpp"

/*  Class LevelEntity */

/*  Empty constructor */
LevelEntity::LevelEntity()
{
  x = 0;
  y = 0;
  width = 0;
  height = 0;
  StoreOriginalValues();
  position = sf::Vector2f(0, 0);
  rect = sf::Rect<float>(x, y, width, height);
  sprite = sf::Sprite();
}

/*  Standard constructor */
LevelEntity::LevelEntity(float x, float y, float width, float height, std::string image_path, int type)
{
  this->x = x;
  this->y = y;
  position = sf::Vector2f(x, y);
  this->width = width;
  this->height = height;
  StoreOriginalValues();
  rect = sf::Rect<float>(x, y, width, height);
  img_path = image_path;
  // Try to load a texture from img_path
  CreateSprite();
  this->type = type;

}


/* Try to load texture from img_path and construct sprite */
void LevelEntity::CreateSprite()
{
  if (! texture.loadFromFile(img_path) )
  {
    // Create an empty sprite
    sprite = sf::Sprite();
  }
  else
  {
    sprite = sf::Sprite(texture, sf::Rect<int>(0, 0, (int) width, (int) height));
  }
  sprite.setPosition(x, y);
}

/* Copy constructor */
LevelEntity::LevelEntity(const LevelEntity &level_entity)
{
  x = level_entity.x;
  y = level_entity.y;
  position = sf::Vector2f(x, y);
  width = level_entity.width;
  height = level_entity.height;
  StoreOriginalValues();
  rect = sf::Rect<float>(x, y, width, height);
  img_path = level_entity.img_path;
  // Try to load texture
  CreateSprite();
  type = level_entity.type;
}

/*  Assignment operator overload */
LevelEntity& LevelEntity::operator=(const LevelEntity &level_entity)
{
  x = level_entity.x;
  y = level_entity.y;
  position = sf::Vector2f(x, y);
  width = level_entity.width;
  height = level_entity.height;
  StoreOriginalValues();
  rect = sf::Rect<float>(x, y, width, height);
  img_path = level_entity.img_path;
  // Try to load texture
  CreateSprite();
  type = level_entity.type;

  return *this;
}

/* Print overload */
std::ostream& operator<<(std::ostream &os, const LevelEntity &level_entity)
{
  os << "LevelEntity, x: " << level_entity.x << ", y: " << level_entity.y;
  os << ", width: " << level_entity.width << ", height: " << level_entity.height;
  os << std::endl;
  return os;

}

/* Set new position */
void LevelEntity::setPosition(float x, float y)
{
  this->x = x;
  this->y = y;
  position = sf::Vector2f(x, y);
  rect = sf::Rect<float>(x, y, width, height);
  sprite.setPosition(x, y);
  StoreOriginalValues();
}

/* Set new positition */
void LevelEntity::setPosition(sf::Vector2f position)
{
  this->position = position;
  x = position.x;
  y = position.y;
  rect = sf::Rect<float>(x, y, width, height);
  sprite.setPosition(x, y);
  StoreOriginalValues();
}

/*  Get position */
const sf::Vector2f& LevelEntity::getPosition()
{
  return position;
}

/* Check if position inside LevelEntity */
bool LevelEntity::isInside(float x, float y)
{
  return rect.contains(x, y);
}

/* Set positioned */
void LevelEntity::setPositioned(bool positioned)
{
  this->positioned = positioned;
}

/* Return positioned */
bool LevelEntity::getPositioned()
{
  return positioned;
}

/* Return type */
int LevelEntity::getType()
{
  return type;
}

/*  Draw LevelEntity */
void LevelEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(sprite, states);
}

/* Flip / unflip LevelEntity */
void LevelEntity::flipLevelEntity()
{
  if (flippable)
  {
    if (flipped)
    {
      sprite.setTextureRect(sf::IntRect(0, 0, width, height));
      flipped = false;
    }
    else
    {
      sprite.setTextureRect(sf::IntRect(width, 0, -width, height));
      flipped = true;
    }
  }

}

/*  Return width */
float LevelEntity::getWidth()
{
  return width;
}

/*  Return height */
float LevelEntity::getHeight()
{
  return height;
}

/*  Get orientation */
int LevelEntity::getOrientation()
{
  if (flipped)
  {
    return 0;
  }
  return 1;
}

/* Set stretchable */
void LevelEntity::setStretchable(bool enable)
{
  stretchable = enable;
}

/*  Get stretchable */
bool LevelEntity::getStretchable()
{
  return stretchable;
}

/*  Set fully_constructed */
void LevelEntity::setFullyConstructed()
{
  fully_constructed = true;
}

/*  Get fully_constructed */
bool LevelEntity::getFullyConstructed()
{
  return fully_constructed;
}

/*  Try to activate stretching */
void LevelEntity::activateStretching(float x, float y)
{
  // Give quite generous 'hitboxes' for stretching
  if ( (y > this->y - 10) && (y < this->y + height))
  {
    if ((this->x - 10 < x) &&  (x < this->x + width + 10))
    {
      stretchable = true;
    }
  }

}

/* Stretch LevelEntity */
void LevelEntity::stretch(float x, float y)
{
  if (stretchable)
  {
    // Set new width
    if (x > orig_x)
    {
      width = x - orig_x;
      this->x = orig_x;
    }
    else
    {
      this->x = x;
      width = orig_x - x;
    }
    if (y >= orig_y)
    {
      // Set new y and update also height
      // Try to keep this->y as the upper corner position
      if (y < orig_y + orig_height)
      {
        this->y = y;
        height =  orig_y + orig_height - y;
      }
      else
      {
        this->y = orig_y + orig_height;
        height = y - this->y;
      }

    }

    else
    {
      this->y = y;
      height = orig_height + orig_y - y;
    }

    // Update positions and image
    rect = sf::Rect<float>(this->x, this->y, width, height);
    sprite.setPosition(this->x, this->y);
    position = sf::Vector2f(this->x, this->y);
    sprite.setScale(width / orig_width, height / orig_height);
  }
}


/*  Store original values */
void LevelEntity::StoreOriginalValues()
{
  orig_x = x;
  orig_y = y;
  orig_width = width;
  orig_height = height;
}

void LevelEntity::setNonFlippable()
{
  flippable = false;
}

float LevelEntity::getX()
{
  return x;
}

float LevelEntity::getY()
{
  return y;
}

/*  Stretch LevelEntity (ground) to correct size */
void LevelEntity::autoStretch(float width, float height)
{
  // Update image
  rect = sf::Rect<float>(x, y, width, height);
  sprite.setScale(width / orig_width, height / orig_height);
  // Update width and height
  this->height = height;
  this->width = width;
}

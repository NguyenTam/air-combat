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
}

/* Copy constructor */
LevelEntity::LevelEntity(const LevelEntity &level_entity)
{
  x = level_entity.x;
  y = level_entity.y;
  position = sf::Vector2f(x, y);
  width = level_entity.width;
  height = level_entity.height;
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
}

/* Set new positition */
void LevelEntity::setPosition(sf::Vector2f position)
{
  this->position = position;
  x = position.x;
  y = position.y;
  rect = sf::Rect<float>(x, y, width, height);
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

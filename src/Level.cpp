/**
  *   @file Level.cpp
  *   @brief Source code for class Level.cpp
  */

#include "Level.hpp"

/*  Class Level */

/* Constructor */
Level::Level()
{
  // Constuct empty LevelEntity
  current_entity = std::make_shared<LevelEntity>();
}

/* Set level_y_limit */
void Level::setYLimit(float y_limit)
{
  level_y_limit = y_limit;
}


/* Check if position free */
bool Level::CheckPosition(float x, float y, float width, float height, LevelEntity *cmp)
{
  // Go through LevelEntities and check all four corners
  for (auto it = level_entities.begin(); it != level_entities.end(); it++)
  {
    if ( it->get() != cmp)
    {
      if ( (*it)->isInside(x, y) )
      {
        // Top left corner inside some other LevelEntity
        return false;
      }
      else if ( (*it)->isInside(x + width, y) )
      {
        // Right top corner inside some other LevelEntity
        return false;

      }
      else if ( (*it)->isInside(x, y + width) )
      {
        // Left bottom corner inside some other LevelEntity
        return false;
      }
      else if ( (*it)->isInside(x + width, y + height) )
      {
        // Right bottom corner inside some other LevelEntity
        return false;

      }
    }
  }

  return true;
}



/* Try to remove an entity */
void Level::EraseEntity(float x, float y)
{
  // Go through all LevelEntities
  for (auto it = level_entities.begin(); it != level_entities.end(); it++)
  {
    if ( (*it)->isInside(x, y) )
    {
      // Remove this entity
      level_entities.erase(it);
      break;
    }
  }
}


/* Add LevelEntity */
void Level::addEntity(float x, float y, int entity_type)
{
  // Check that x and y are non negative, y_limit check needs to be done
  // in called methods (e.g. AddInfantry) itself
  if (x < 0)
  {
    x = 0;
  }
  if (y < 0)
  {
    y = 0;
  }

  if (entity_type == INFANTRY_ENTITY)
  {
    AddInfantry(x, y);
  }
  else if (entity_type == PLANE_ENTITY)
  {
    AddPlane(x, y);
  }
  else if( entity_type == ERASE_ENTITY )
  {
    EraseEntity(x, y);
  }
}

/* Try to add an infantry entity */
void Level::AddInfantry(float x, float y)
{
  current_entity_height = infantry_height;
  // Check the level lower y limit
  if (y + infantry_height > level_y_limit)
  {
    y = level_y_limit - infantry_height;
  }

  if ( current_entity->getType() == INFANTRY_ENTITY && current_entity->getPositioned() == false )
  {
    // Try to position current_entity
    if ( CheckPosition(x, y, infantry_width, infantry_height, current_entity.get()) )
    {
      // position ok
      current_entity->setPosition(x, y);
      current_entity->setPositioned(true);

    }
  }
  else if (current_entity->getType() == INFANTRY_ENTITY || current_entity->getType() == NO_ENTITY)
  {
    // Construct new infantry entity
    current_entity = std::make_shared<LevelEntity>(x, y, infantry_width, infantry_height,
                    infantry_path, INFANTRY_ENTITY);
    level_entities.push_back(current_entity);

  }
  else
  {
    // Remove current_entity from level_entities
    removeCurrent();
    // Construct new infantry entity

    current_entity = std::make_shared<LevelEntity>(x, y, infantry_width, infantry_height,
                    infantry_path, INFANTRY_ENTITY);
    level_entities.push_back(current_entity);

  }
}


/* Add a plane entity */
void Level::AddPlane(float x, float y)
{
  current_entity_height = plane_height;
  // Check the level lower y limit
  if (y + plane_height > level_y_limit)
  {
    y = level_y_limit - plane_height;
  }

  if ( current_entity->getType() == PLANE_ENTITY && current_entity->getPositioned() == false )
  {
    // Try to position current_entity
    if ( CheckPosition(x, y, plane_width, plane_height, current_entity.get()) )
    {
      // position ok
      current_entity->setPosition(x, y);
      current_entity->setPositioned(true);

    }
  }
  else if (current_entity->getType() == PLANE_ENTITY || current_entity->getType() == NO_ENTITY)
  {
    // Construct new plane entity
    current_entity = std::make_shared<LevelEntity>(x, y, plane_width, plane_height,
                    plane_path, PLANE_ENTITY);
    level_entities.push_back(current_entity);

  }
  else
  {
    // Remove current_entity from level_entities
    removeCurrent();
    // Construct new plane entity

    current_entity = std::make_shared<LevelEntity>(x, y, plane_width, plane_height,
                    plane_path, PLANE_ENTITY);
    level_entities.push_back(current_entity);

  }
}


/* Try to move current_entity */
void Level::moveCurrentEntity(float x, float y)
{
  if (! current_entity->getPositioned())
  {
    // Don't move entity outside level area
    if (x < 0)
    {
      if ( y < 0)
      {
        current_entity->setPosition(0, 0);
      }
      else if (y + current_entity_height > level_y_limit)
      {
        current_entity->setPosition(0, level_y_limit - current_entity_height);
      }
      else
      {
        // Only x incorrect
        current_entity->setPosition(0, y);
      }
    }
    else if (y < 0)
    {
      current_entity->setPosition(x, 0);
    }
    else if (y + current_entity_height > level_y_limit)
    {
      current_entity->setPosition(x, level_y_limit - current_entity_height);
    }
    else
    {
      // Standard situation
      current_entity->setPosition(x, y);
    }

  }
}

/*  Remove current_entity from level_entities */
void Level::removeCurrent()
{
  if (current_entity->getPositioned() && current_entity->getType() != NO_ENTITY)
  {
    // Don't remove just assign an empty entity
    current_entity = std::make_shared<LevelEntity>();
  }
  else if (current_entity->getType() != NO_ENTITY)
  {
    // Remove the entity
    for (auto it = level_entities.begin(); it != level_entities.end(); it++)
    {
      if ( current_entity == (*it))
      {
        level_entities.erase(it);
        // Construct an empty current_entity
        current_entity = std::make_shared<LevelEntity>();
        break;
      }
    }
  }

}

/*  Draw Level */
void Level::drawLevel(sf::RenderWindow &window)
{
  // Draw all LevelEntities
  for (auto it = level_entities.begin(); it != level_entities.end(); it++)
  {
    window.draw( (**it) );
  }
}

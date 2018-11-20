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


/* Check if position free */
bool Level::CheckPosition(float x, float y)
{
  // Go through LevelEntities
  for (auto it = level_entities.begin(); it != level_entities.end(); it++)
  {
    if ( (*it)->isInside(x, y) )
    {
      // Position inside some LevelEntity
      return false;
    }
  }
  return true;
}



/* Try to remove an entity */
bool Level::removeEntity(float x, float y)
{
  // go through all LevelEntities
  for (auto it = level_entities.begin(); it != level_entities.end(); it++)
  {
    if ( (*it)->isInside(x, y) )
    {
      // Remove this entity
      level_entities.erase(it);
      return true;
    }
  }
  return false;
}


/* Add LevelEntity */
void Level::addEntity(float x, float y, int entity_type)
{
  if (entity_type == INFANTRY_ENTITY)
  {
    AddInfantry(x, y);
  }
  else if (entity_type == PLANE_ENTITY)
  {
    AddPlane(x, y);
  }
}

/* Try to add an infantry entity */
void Level::AddInfantry(float x, float y)
{
  if ( current_entity->getType() == INFANTRY_ENTITY && current_entity->getPositioned() == false )
  {
    // Try to position current_entity
    if ( CheckPosition(x, y) )
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
    RemoveCurrent();
    // Construct new infantry entity

    current_entity = std::make_shared<LevelEntity>(x, y, infantry_width, infantry_height,
                    infantry_path, INFANTRY_ENTITY);
    level_entities.push_back(current_entity);

  }
}


/* Add a plane entity */
void Level::AddPlane(float x, float y)
{
  if ( current_entity->getType() == PLANE_ENTITY && current_entity->getPositioned() == false )
  {
    // Try to position current_entity
    if ( CheckPosition(x, y) )
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
    RemoveCurrent();
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
    current_entity->setPosition(x, y);
  }
}

/*  Remove current_entity from level_entities */
void Level::RemoveCurrent()
{
  for (auto it = level_entities.begin(); it != level_entities.end(); it++)
  {
    if ( current_entity == (*it))
    {
      level_entities.erase(it);
      break;
    }
  }
}

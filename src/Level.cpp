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
  sf::Rect<float> cmp_rect = sf::Rect<float>(x, y, width, height);
  // Go through LevelEntities and check all four corners
  for (auto it = level_entities.begin(); it != level_entities.end(); it++)
  {
    // Remark many check are needed bacause entity sizes can be anything
    // Thus, entites can be partially or complitely inside each other

    if ( it->get() != cmp)
    {
      float entity_width = (*it)->getWidth();
      float entity_height = (*it)->getHeight();
      sf::Vector2f entity_pos = (*it)->getPosition();

      // Check whether enity is inside cmp_rect
      if (cmp_rect.contains(entity_pos.x, entity_pos.y))
      {
        // Entity top left corner inside
        return false;
      }
      else if (cmp_rect.contains(entity_pos.x + entity_width, entity_pos.y))
      {
        // Top right corner inside
        return false;
      }
      else if (cmp_rect.contains(entity_pos.x, entity_pos.y + height))
      {
        // Bottom left corner inside
        return false;
      }
      else if (cmp_rect.contains(entity_pos.x + entity_width, entity_pos.y + entity_height))
      {
        // Botton right inside
        return false;
      }
      else if (cmp_rect.contains(entity_pos.x + entity_width/2, entity_pos.y + entity_height/2))
      {
        // Center inside (complitely inside cmp_rect)
        return false;
      }
      else if ( (*it)->isInside(x, y) )
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

  // Go through all entity_type and try to create correct LevelEntity
  if (entity_type == FRIENDLY_INFANTRY)
  {
    AddEntity(x, y, FRIENDLY_INFANTRY, infantry_width, infantry_height, friendly_infantry_path);
  }
  else if (entity_type == HOSTILE_INFANTRY)
  {
    AddEntity(x, y, HOSTILE_INFANTRY, infantry_width, infantry_height, hostile_infantry_path);
  }
  else if (entity_type == FRIENDLY_PLANE)
  {
    AddEntity(x, y, FRIENDLY_PLANE, plane_width, plane_height, friendly_plane_path);
  }
  else if (entity_type == HOSTILE_PLANE)
  {
    AddEntity(x, y, HOSTILE_PLANE, plane_width, plane_height, hostile_plane_path);
  }
  else if (entity_type == FRIENDLY_AA)
  {
    AddEntity(x, y, FRIENDLY_AA, AA_width, AA_height, friendly_AA_path);
  }
  else if (entity_type == HOSTILE_AA)
  {
    AddEntity(x, y, HOSTILE_AA, AA_width, AA_height, hostile_AA_path);
  }
  else if (entity_type == FRIENDLY_HANGAR)
  {
    AddEntity(x, y, FRIENDLY_HANGAR, hangar_width, hangar_height, friendly_hangar_path);
  }
  else if (entity_type == HOSTILE_HANGAR)
  {
    AddEntity(x, y, HOSTILE_HANGAR, hangar_width, hangar_height, hostile_hangar_path);
  }
  else if (entity_type == FRIENDLY_BASE)
  {
    AddEntity(x, y, FRIENDLY_BASE, base_width, base_height, friendly_base_path);
  }
  else if (entity_type == HOSTILE_BASE)
  {
    AddEntity(x, y, HOSTILE_BASE, base_width, base_height, hostile_base_path);
  }
  else if (entity_type == TREE_ENTITY)
  {
    AddEntity(x, y, TREE_ENTITY, tree_width, tree_height, tree_path);
  }
  else if (entity_type == ROCK_ENTITY)
  {
    AddEntity(x, y, ROCK_ENTITY, rock_width, rock_height, rock_path);
  }
  else if( entity_type == ERASE_ENTITY )
  {
    EraseEntity(x, y);
  }
}




/* Try to add an infantry entity */
void Level::AddEntity(float x, float y, int entity_type, float entity_width, float entity_height, std::string entity_img)
{
  current_entity_height = entity_height;
  // Check the level lower y limit
  if (y + entity_height > level_y_limit)
  {
    y = level_y_limit - entity_height;
  }

  if ( current_entity->getType() == entity_type && current_entity->getPositioned() == false )
  {
    // Try to position current_entity
    if ( CheckPosition(x, y, entity_width, entity_height, current_entity.get()) )
    {
      // position ok
      current_entity->setPosition(x, y);
      current_entity->setPositioned(true);

    }
  }
  else if (current_entity->getType() == entity_type || current_entity->getType() == NO_ENTITY)
  {
    // Construct new entity_type LevelEntity
    current_entity = std::make_shared<LevelEntity>(x, y, entity_width, entity_height,
                    entity_img, entity_type);
    level_entities.push_back(current_entity);

  }
  else
  {
    // Remove current_entity from level_entities
    removeCurrent();
    // Construct new entity_type LevelEntity

    current_entity = std::make_shared<LevelEntity>(x, y, entity_width, entity_height,
                    entity_img, entity_type);
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

/* Try to flip LevelEntity */
void Level::flipEntity(float x, float y)
{
  for (auto it = level_entities.begin(); it != level_entities.end(); it++)
  {
    if ((*it)->isInside(x, y))
    {
      (*it)->flipLevelEntity();
      break;
    }
  }
}

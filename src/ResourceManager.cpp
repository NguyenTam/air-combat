#include "ResourceManager.hpp"
#include <iostream>

ResourceManager::ResourceManager()
{
  try
  {
    for (int enum_value = 0; enum_value != Textures::ID::id_end; enum_value++)
    {
      load(static_cast<Textures::ID>(enum_value), Paths::Paths[Paths::PATHS::img] +Textures::TextureFiles[enum_value]);
    }
  }
  catch (std::runtime_error& e)
  {
    std::cout << "Exception: " << e.what() << std::endl;
  }
}

void ResourceManager::load(Textures::ID id, const std::string& filename)
{
  std::unique_ptr<sf::Texture> resource(new sf::Texture());
  if (!resource->loadFromFile(filename))
    throw std::runtime_error("ResrouceManager::load - Failed to load " + filename);
  insertResource(id, resource);
}

const sf::Texture& ResourceManager::get(Textures::ID id) const
{
  auto found = resourceMap.find(id);
  assert(found != resourceMap.end());

  return *found->second;
}

sf::Texture & ResourceManager::get(Textures::ID id)
{
  auto found = resourceMap.find(id);
  assert(found != resourceMap.end());

  return *found->second;
  
}

/**
 * New textures will be actually inserted here. std::move is used to move the ownership of resource to std::make_pair.
 */
void ResourceManager::insertResource(Textures::ID id, std::unique_ptr<sf::Texture> &resource)
{
  // Insert and check success
  auto inserted = resourceMap.insert(std::make_pair(id, std::move(resource)));
  assert(inserted.second);
}

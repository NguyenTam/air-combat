#include "ResourceManager.hpp"
#include <iostream>
bool ResourceManager::init()
{
  //TODO: More resources, after we have decided image names
  try
    {
      load(Textures::BlueAirplane,   "../data/img/fplane_alpha.png");
      load(Textures::BlueAntiAircraft,  "../data/img/fAA_alpha.png");      
      return true;
    }
  catch (std::runtime_error& e)
    {
      std::cout << "Exception: " << e.what() << std::endl;
      return false;
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

void ResourceManager::insertResource(Textures::ID id, std::unique_ptr<sf::Texture> &resource)
{
  // Insert and check success
  auto inserted = resourceMap.insert(std::make_pair(id, std::move(resource)));
  assert(inserted.second);
}

/**
 * @file ResourceManager.hpp
 * @brief Resource manager which load and distribute resources (textures). The owner of resources is only this class, that's why unique pointer is used. Once this instance is out of scope, resources will be destroyed automatically by smart pointer. RAII.
 */
#pragma once
#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>
#include <SFML/Graphics.hpp>
#include "CommonDefinitions.hpp"

class ResourceManager{
public:
  ResourceManager();
  /**
   * @brief get a texture based on texture ID.
   * @param id, resource enum id.
   * @return a texture reference from the resource map.
   */
  sf::Texture & get(Textures::ID id);
  /**
   * @brief get a texture based on texture ID.
   * @param id, resource enum id.
   * @return a texture reference from the resource map.
   */
  const sf::Texture & get(Textures::ID id) const;
private:
  /**
   * @brief insert a resource to resource map.
   * @param id, resource enum id.
   * @return  a reference to found texture.
   */
  void insertResource(Textures::ID id, std::unique_ptr<sf::Texture> &resource);

  /**
   * @brief try load a texture from a filename to resource map. This function use @see insertResource()
   * @param id, resource enum id.
   * @param filename, file path to resource
   */
  void load(Textures::ID id, const std::string& filename);

  std::map<Textures::ID,std::unique_ptr<sf::Texture>> resourceMap; /**< A map containing Texture ID as a key and SFML texture as a value is pointer to texture. Map is used over vector, because */
  
};

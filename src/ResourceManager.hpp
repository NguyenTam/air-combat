#pragma once
#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>
#include <SFML/Graphics.hpp>
namespace Textures
{
  enum ID
    {
      BlueAirplane,
      BlueAntiAircraft,
      BlueBase,
      BlueHangar,
      BlueInfantry,
      RedAirplane,
      RedAntiAircraft,
      RedBase,
      RedHangar,
      RedInfantry
    };
}

class ResourceManager{
public:
  bool init();
  sf::Texture & get(Textures::ID id);
  const sf::Texture & get(Textures::ID id) const;  
private:
  void insertResource(Textures::ID id, std::unique_ptr<sf::Texture> &resource);
  void load(Textures::ID id, const std::string& filename);
  
  std::map<Textures::ID,std::unique_ptr<sf::Texture>> resourceMap;
  
};

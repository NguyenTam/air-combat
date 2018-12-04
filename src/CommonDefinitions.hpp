/**
 *   @file CommonDefinitions.hpp
 *   @brief Header for CommonDefinitions class
 */
#pragma once

/* Includes */

#include <string>
#include <vector>
#include <map>
namespace Game
{
  extern const int WIDTH;
  extern const int HEIGHT;
}

namespace Paths
{
  enum PATHS
    {
      fonts,
      img,
      level_files,
      logs
    };
  extern std::vector<std::string> Paths;
  
}

namespace Textures
{
  enum ID
    {
      BlueAirplane_alpha,
      BlueAirplane,
      BlueAntiAircraft_alpha,
      BlueAntiAircraft,
      BlueBase_alpha,
      BlueBase,
      BlueHangar_alpha,
      BlueHangar,
      BlueInfantry_alpha,
      BlueInfantry,
      Bullet_alpha,
      erase,
      Ground_alpha,
      Ground,
      infantry,
      left_arrow,
      plane,
      RedAirplane_alpha,
      RedAirplane,
      RedAntiAircraft_alpha,
      RedAntiAircraft,
      RedBase_alpha,
      RedBase,
      RedHangar_alpha,
      RedHangar,
      RedInfantry_alpha,
      RedInfantry,
      right_arrow,
      Rock_alpha,
      Rock,
      std_button,
      Tree_alpha,
      Tree,
      end      
    };
  extern std::vector<std::string> TextureFiles;
extern std::map<std::string, Textures::ID> alphaTextures;
}


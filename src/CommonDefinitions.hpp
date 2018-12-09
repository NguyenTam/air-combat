/**
 *   @file CommonDefinitions.hpp
 *   @brief Header for CommonDefinitions class
 */
#pragma once

/* Includes */

#include <string>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>

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
      id_end
    };
  extern std::vector<std::string> TextureFiles;
  extern std::map<std::string, Textures::ID> alphaTextures;
}


namespace Game
{
  extern const int WIDTH;
  extern const int HEIGHT;
  extern const float GRAVITY;
  extern const float TOPIXELS;
  extern const float TOMETERS;
  extern const int LEFT_LIMIT;
  extern const int RIGHT_LIMIT;
  extern const int UPPER_LIMIT;
  extern const int LOWER_LIMIT;


  enum TYPE_ID
    {
      airplane,
      antiaircraft,
      base,
      hangar,
      infantry,
      bullet,
      ground,
      rock,
      tree,
      type_id_end
    };

  enum TEAM_ID
    {
      all_friend,
      all_enemy,
      blue,
      red,
      team_id_end
    };

    enum ACTIONS
      {
	move_left,
	move_right,
	move_up,
	move_down,
	shoot,
	bomb,
	nothing,
	actions_end
      };

  extern std::map<ACTIONS, sf::Vector2f> actions_and_directions;
  extern std::map<Textures::ID, int> sensor_radius;

  enum GameMode
  {
    SinglePlayer,
    Multiplayer,
  };
}

namespace Paths
{
  enum PATHS
    {
      fonts,
      img,
      level_files,
      logs,
      stats_log,
      paths_end
    };
  extern std::vector<std::string> Paths;

}

namespace Fonts
{
  enum FONTS
    {
      arial,
      courier,
      sansation
    };

    extern std::map<FONTS, std::string> font_files;
}

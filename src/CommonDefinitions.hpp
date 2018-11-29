#pragma once
#include <string>
#include <vector>
namespace Game
{
  extern const int WIDTH;
  extern const int HEIGHT;
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
	erase,
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
	rock_alpha,
	rock,
	std_button,
	tree_alpha,
	tree,
	  end
      }; /**< Use this command in data/img "ls -1 | sort | sed -e 's/\..*$/,/'" to get this output. */
  extern std::vector<std::string> TextureFiles; /**< Use this command in data/img "ls -1 | sort | sed -e 's/$/",/' | sed -e 's/^/"/'" to get this output. */
}


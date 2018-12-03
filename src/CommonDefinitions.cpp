#include "CommonDefinitions.hpp"
namespace Game
{
const int WIDTH = 800;
const int HEIGHT = 600;
}

namespace Paths
{
std::vector<std::string> Paths
{
  "../data/fonts/",
      "../data/img/",
      "../data/level_files/",
      "../data/logs/"      
      };
}

namespace Textures
{

std::vector<std::string> TextureFiles {
  "BlueAirplane_alpha.png",
      "BlueAirplane.png",
      "BlueAntiAircraft_alpha.png",
      "BlueAntiAircraft.png",
      "BlueBase_alpha.png",
      "BlueBase.png",
      "BlueHangar_alpha.png",
      "BlueHangar.png",
      "BlueInfantry_alpha.png",
      "BlueInfantry.png",
      "Bullet_alpha.png",
      "erase.png",
      "Ground_alpha.png",
      "Ground.png",
      "infantry.png",
      "left_arrow.png",
      "plane.png",
      "RedAirplane_alpha.png",
      "RedAirplane.png",
      "RedAntiAircraft_alpha.png",
      "RedAntiAircraft.png",
      "RedBase_alpha.png",
      "RedBase.png",
      "RedHangar_alpha.png",
      "RedHangar.png",
      "RedInfantry_alpha.png",
      "RedInfantry.png",
      "right_arrow.png",
      "Rock_alpha.png",
      "Rock.png",
      "std_button.png",
      "Tree_alpha.png",
      "Tree.png"
};

std::map<std::string, Textures::ID> alphaTextures
{
  { "BlueAirplane", BlueAirplane_alpha },
  { "BlueAntiAircraft", BlueAntiAircraft_alpha },
  { "BlueBase", BlueBase_alpha },
  { "BlueHangar", BlueHangar_alpha },
  { "BlueInfantry", BlueInfantry_alpha },
  { "Bullet", Bullet_alpha },
  { "Ground", Ground_alpha },
  { "RedAirplane", RedAirplane_alpha },
  { "RedAntiAircraft", RedAntiAircraft_alpha },
  { "RedBase", RedBase_alpha },
  { "RedHangar", RedHangar_alpha },
  { "RedInfantry", RedInfantry_alpha },
  { "Rock", Rock_alpha },
  { "Tree", Tree_alpha }     
};
}

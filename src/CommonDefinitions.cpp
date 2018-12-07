#include "CommonDefinitions.hpp"
namespace Game
{
  const int WIDTH = 1200;
  const int HEIGHT = 600;
  const float GRAVITY = 0.1f;
  const float TOPIXELS = 5.f;
  const float TOMETERS = 1/TOPIXELS;
  const int LEFT_LIMIT = int(0.01*WIDTH+0.5);       //limit as percentage from the limits of the map. 
  const int RIGHT_LIMIT = int((1-0.01)*WIDTH+0.5);  //these 3 values should be between 0.01 and 0.25.
  const int UPPER_LIMIT = int((1-0.01)*HEIGHT+0.5);
  const int LOWER_LIMIT = int(0.3*HEIGHT+0.5);      //LOWER_LIMIT should be atleast 0.3.


  std::map<ACTIONS, sf::Vector2f> actions_and_directions
    {
      { ACTIONS::move_left, sf::Vector2f(-1.f, 0.f)},
      { ACTIONS::move_right, sf::Vector2f(1.f, 0.f)},
      {	ACTIONS::move_up, sf::Vector2f(0.f, -1.f)},
      { ACTIONS::move_down,sf::Vector2f(0.f, 1.f)},
      { ACTIONS::shoot, sf::Vector2f(-1.f, 0.f) },
      {	ACTIONS::bomb, sf::Vector2f(0.f, 1.f) },
      { ACTIONS::nothing,sf::Vector2f(0.f, 0.f) }
    };
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

namespace Fonts
{
  std::map<FONTS, std::string> font_files
  {
    {FONTS::arial, "arial.ttf" },
    {FONTS::courier, "Courier.ttf" },
    {FONTS::sansation, "Sansation.ttf" }
  };
}

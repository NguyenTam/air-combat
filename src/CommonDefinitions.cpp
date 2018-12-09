#include "CommonDefinitions.hpp"
namespace Game
{
  const int WIDTH = 1200;
  const int HEIGHT = 600;
  const float GRAVITY = 0.1f;
  constexpr float TOPIXELS = 5.f;
  constexpr float TOMETERS = 1/TOPIXELS;
  constexpr int LEFT_LIMIT = static_cast<int>(0.01*WIDTH);       //limit as percentage from the limits of the map.
  constexpr int RIGHT_LIMIT = static_cast<int>((1-0.1)*WIDTH);  //these 3 values should be between 0.01 and 0.25.
  constexpr int UPPER_LIMIT = static_cast<int>((0.2)*HEIGHT);
  constexpr int LOWER_LIMIT = static_cast<int>((1-0.3)*HEIGHT);      //LOWER_LIMIT should be atleast 0.3.


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

  std::map<Textures::ID, int> sensor_radius
    {
      { Textures::ID::BlueAirplane_alpha, 80 },
      { Textures::ID::BlueAirplane, 80 },
      { Textures::ID::BlueAntiAircraft_alpha, 120 },
      { Textures::ID::BlueAntiAircraft, 120 },
      { Textures::ID::BlueBase_alpha, 0 },
      { Textures::ID::BlueBase, 0 },
      { Textures::ID::BlueHangar_alpha, 0 },
      { Textures::ID::BlueHangar, 0 },
      { Textures::ID::BlueInfantry_alpha, 50 },
      { Textures::ID::BlueInfantry, 50 },
      { Textures::ID::Bullet_alpha, 0 },
      { Textures::ID::Ground_alpha, 0 },
      { Textures::ID::Ground, 0 },
      { Textures::ID::RedAirplane_alpha, 80 },
      { Textures::ID::RedAirplane, 80 },
      { Textures::ID::RedAntiAircraft_alpha, 120 },
      { Textures::ID::RedAntiAircraft, 120 },
      { Textures::ID::RedBase_alpha, 0 },
      { Textures::ID::RedBase, 0 },
      { Textures::ID::RedHangar_alpha, 0 },
      { Textures::ID::RedHangar, 0 },
      { Textures::ID::RedInfantry_alpha, 50 },
      { Textures::ID::RedInfantry, 50 },
      { Textures::ID::Rock_alpha, 0 },
      { Textures::ID::Rock, 0 },
      { Textures::ID::Tree_alpha, 0 },
      { Textures::ID::Tree, 0 }
    };

} // namespace Game

namespace Paths
{
std::vector<std::string> Paths
{
  "../data/fonts/",
      "../data/img/",
      "../data/level_files/",
      "../data/logs/" ,
      "../data/misc/stats.txt"     
      };
} // namespace Paths

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
} // namespace Textures

namespace Fonts
{
  std::map<FONTS, std::string> font_files
  {
    {FONTS::arial, "arial.ttf" },
    {FONTS::courier, "Courier.ttf" },
    {FONTS::sansation, "Sansation.ttf" }
  };
} // namespace Fonts

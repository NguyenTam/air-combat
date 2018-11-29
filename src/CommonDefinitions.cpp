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
    "../data/level_files/"      
  };
}

namespace Textures
{

  std::vector<std::string> TextureFiles
    {
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
	"erase.png",
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
	"rock_alpha.png",
	"rock.png",
	"std_button.png",
	"tree_alpha.png",
	"tree.png"
    }; /**< Use this command in data/img "ls -1 | sort | sed -e 's/$/",/' | sed -e 's/^/"/'" to get this output. */
}

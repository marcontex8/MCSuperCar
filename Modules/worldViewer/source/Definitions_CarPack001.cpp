#include "Definitions_CarPack001.h"
#include "Diagnostics.h"

extern Diagnostics diagnostics;

namespace carPack001{

	const std::string carPack_path = R"(D:\WorkSpace\MCSuperCar\Modules\worldViewer\graphic\CarPack001\)";
	const std::string opticsTexture_path = R"(D:\WorkSpace\MCSuperCar\Modules\worldViewer\graphic\CarPack001\Textures\Optics.jpg)";



	std::map<Model, std::string> modelsStrings{
		std::pair(Model::Compact,	"Compact"),
		std::pair(Model::Coupe,		"Coupe"),
		std::pair(Model::Hatchback,	"Hatchback"),
		std::pair(Model::Minivan,	"Minivan"),
		std::pair(Model::Offroad,	"Offroad"),
		std::pair(Model::Pickup,	"Pickup"),
		std::pair(Model::Sedan,		"Sedan"),
		std::pair(Model::Sport,		"Sport"),
		std::pair(Model::SUV,		"SUV"),
		std::pair(Model::Wagon,		"Wagon")
	};




	std::map<Color, std::string> colorsStrings{
		std::pair(Color::Black,	"Black"),
		std::pair(Color::Blue,		"Blue"),
		std::pair(Color::Green,	"Green"),
		std::pair(Color::Yellow,	"Yellow"),
		std::pair(Color::White,	"White"),
		std::pair(Color::Red,		"Red"),
	};

	enum class Wheel {
		A, B, C, D, E, F, G, H
	};

	std::map<Wheel, std::string> wheelsStrings{
		std::pair(Wheel::A, "A"),
		std::pair(Wheel::B, "B"),
		std::pair(Wheel::C, "C"),
		std::pair(Wheel::D, "D"),
		std::pair(Wheel::E, "E"),
		std::pair(Wheel::F, "F"),
		std::pair(Wheel::G, "G"),
		std::pair(Wheel::H, "H")
	};

	std::map<Model, Wheel> modelWheel{
		std::pair(Model::Compact,	Wheel::C),
		std::pair(Model::Coupe,		Wheel::F),
		std::pair(Model::Hatchback,	Wheel::B),
		std::pair(Model::Minivan,	Wheel::D),
		std::pair(Model::Offroad,	Wheel::G),
		std::pair(Model::Pickup,	Wheel::E),
		std::pair(Model::Sedan,		Wheel::A),
		std::pair(Model::Sport,		Wheel::H),
		std::pair(Model::SUV,		Wheel::E),
		std::pair(Model::Wagon,		Wheel::A)
	};

	const Paths getPaths(Model model, Color color) {
		Paths requiredPaths;
		std::string texturesPath = carPack_path + "\\Textures\\" + modelsStrings[model] + "\\";
		requiredPaths.model = carPack_path + "\\Meshes FBX\\" + modelsStrings[model] + ".FBX";
		//diagnostics.log("model: " + requiredPaths.model, Diagnostics::Topic::Viewer);

		requiredPaths.bodyDiffuseTexture = texturesPath +
			modelsStrings[model] + colorsStrings[color] + ".png";
		//diagnostics.log("bodyDiffuseTexture: " + requiredPaths.bodyDiffuseTexture, Diagnostics::Topic::Viewer);

		requiredPaths.bodyGlossinTexture = texturesPath +
			modelsStrings[model] + "_Glossiness.png";
		//diagnostics.log("bodyGlossinTexture: " + requiredPaths.bodyGlossinTexture, Diagnostics::Topic::Viewer);

		requiredPaths.opticsTexture = opticsTexture_path;

		std::string wheelLetter = wheelsStrings[modelWheel[model]];
		requiredPaths.wheelDiffuseTexture = texturesPath + "wheel_" + wheelLetter + "_Diffuse.png";
		//diagnostics.log("wheelDiffuseTexture: " + requiredPaths.wheelDiffuseTexture, Diagnostics::Topic::Viewer);
		requiredPaths.wheelGlossinTexture = texturesPath + "wheel_" + wheelLetter + "_Glossiness.png";;

		//diagnostics.log("wheelGlossinTexture: " + requiredPaths.wheelGlossinTexture, Diagnostics::Topic::Viewer);
		return requiredPaths;
	};

}

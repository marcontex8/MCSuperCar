#ifndef DEFINITIONS_CARPACK001_H
#define DEFINITIONS_CARPACK001_H

#include<string>
#include<map>
#include<vector>

namespace carPack001 {
	enum class Model {
		Compact,
		Coupe,
		Hatchback,
		Minivan,
		Offroad,
		Pickup,
		Sedan,
		Sport,
		SUV,
		Wagon
	};

	enum class Color {
		Black,
		Blue,
		Green,
		Yellow,
		White,
		Red,
	};

	struct Paths {
		std::string model;
		std::string bodyDiffuseTexture;
		std::string bodyGlossinTexture;
		std::string opticsTexture;
		std::string wheelDiffuseTexture;
		std::string wheelGlossinTexture;
	};

	const Paths getPaths(Model model, Color color);
};

#endif
#pragma once

#include "shapes/Sphere.hpp"
#include "planetary-system/CelestialBody.hpp"

#include <fstream>
#include <utility>

#include <nlohmann/json.hpp>


namespace {

}

namespace planetary_system {
	class CelestialBodyDataLoader {
		public:
			static std::pair<CelestialBodyParams, shapes::ShapeOrientationData> 
				parseCelestialBodyConfig(std::string_view config_file_path) {
				std::ifstream config_file{ config_file_path.data()};
				nlohmann::json config_json{ nlohmann::json::parse(config_file) };
			}
	};
}
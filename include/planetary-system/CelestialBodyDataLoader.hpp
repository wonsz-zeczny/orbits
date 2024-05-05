#pragma once

#include "shapes/Sphere.hpp"
#include "planetary-system/CelestialBody.hpp"

#include <nlohmann/json.hpp>

#include <utility>


namespace planetary_system::celestial_body_data_loader {
	std::pair<CelestialBodyParams, shapes::ShapeOrientationData>
		parseCelestialBodyConfig(std::string_view config_file_path);
}

namespace planetary_system::celestial_body_data_loader::internal {
	CelestialBodyParams parseCelestialBodyParams(const nlohmann::json& config_json);
	shapes::ShapeOrientationData parseShapeOrientationData(const nlohmann::json& config_json);
}
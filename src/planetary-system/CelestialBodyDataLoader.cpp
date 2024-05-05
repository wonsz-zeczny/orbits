#include "planetary-system/CelestialBodyDataLoader.hpp"

#include <fstream>


using namespace planetary_system;


std::pair<CelestialBodyParams, shapes::ShapeOrientationData> 
planetary_system::celestial_body_data_loader::parseCelestialBodyConfig(std::string_view config_file_path) {
	std::ifstream config_file{ config_file_path.data() };
	nlohmann::json config_json{ nlohmann::json::parse(config_file) };

	auto celestial_body_params{ celestial_body_data_loader::internal::parseCelestialBodyParams(config_json) };
	auto shape_orientation_data{ celestial_body_data_loader::internal::parseShapeOrientationData(config_json) };

	shape_orientation_data.position.x = celestial_body_params.distance_from_star_au;

	return { celestial_body_params, shape_orientation_data };
}

CelestialBodyParams 
planetary_system::celestial_body_data_loader::internal::parseCelestialBodyParams(const nlohmann::json& config_json) {
	nlohmann::json celestial_body_params_json{ config_json["celestial-body-params"] };

	CelestialBodyParams celestial_body_params;

	celestial_body_params.name = celestial_body_params_json["name"].get<std::string>();
	celestial_body_params.texture_filepath = celestial_body_params_json["texture-name"].get<std::string>();
	celestial_body_params.radius_km = celestial_body_params_json["radius-km"].get<float>();
	celestial_body_params.distance_from_star_au = celestial_body_params_json["distance-from-star-au"].get<float>();
	celestial_body_params.axial_tilt_degrees = celestial_body_params_json["axial-tilt-degrees"].get<float>();
	celestial_body_params.rotation_speed_kmh = celestial_body_params_json["rotation-speed-kmh"].get<float>();
	celestial_body_params.orbital_speed_kmh = celestial_body_params_json["orbital-speed-kmh"].get<float>();

	return celestial_body_params;
}

shapes::ShapeOrientationData 
planetary_system::celestial_body_data_loader::internal::parseShapeOrientationData(const nlohmann::json& config_json) {
	nlohmann::json shape_orientation_data_json{ config_json["shape-orientation-data"] };

	shapes::ShapeOrientationData shape_orientation_data;

	std::vector<float> position{ shape_orientation_data_json["position"].get<std::vector<float>>() };
	std::vector<float> direction{ shape_orientation_data_json["direction"].get<std::vector<float>>() };
	std::vector<float> initial_rotation_axis{ shape_orientation_data_json["initial-rotation-axis"].get<std::vector<float>>() };

	for (auto i{ 0 }; i < position.size(); ++i) {
		shape_orientation_data.position[i] = position.at(i);
	}

	for (auto i{ 0 }; i < direction.size(); ++i) {
		shape_orientation_data.direction[i] = direction.at(i);
	}

	for (auto i{ 0 }; i < initial_rotation_axis.size(); ++i) {
		shape_orientation_data.initial_rotation_axis[i] = initial_rotation_axis.at(i);
	}

	shape_orientation_data.initial_rotation_degrees = shape_orientation_data_json["initial-rotation-degrees"].get<float>();

	return shape_orientation_data;
}

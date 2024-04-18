#pragma once

#include "shapes/Sphere.hpp"

#include <glm/glm.hpp>

#include <string_view>


namespace planetary_system {
	struct CelestialBodyParams {
		std::string_view name;
		std::string_view texture_filepath;
		glm::vec3 position;
		glm::vec3 direction;
		float distance_from_star_au;
		float axial_tilt_degrees;
		float rotation_speed_kmh;
		float orbital_speed_kmh;
	};
	
	class CelestialBody {
		public:
			CelestialBody(CelestialBodyParams&& celestial_body_params);

			void draw() const;
			void drawLines() const;
			void updateVectors();
			void configureSphereGeometry(unsigned int stack_count, unsigned int sector_count, float radius);
			glm::vec3 getPosition() const;
			glm::vec3 getDirection() const;

		private:
			void updatePosition();
			void updateDirection();

			shapes::Sphere sphere{};
			CelestialBodyParams celestial_body_params;
	};
}

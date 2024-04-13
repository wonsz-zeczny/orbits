#pragma once

#include "shapes/Sphere.hpp"

#include <glm/glm.hpp>


namespace planetary_system {
	struct CelestialBodyParams {
		glm::vec3 position;
		glm::vec3 direction;
		float axial_tilt;
		float rotation_speed;
		float orbital_speed;
	};
	
	class CelestialBody {
		public:
			CelestialBody(CelestialBodyParams&& celestial_body_params);

			void draw() const;
			void drawLines() const;
			void configureSphereGeometry(unsigned int stack_count, unsigned int sector_count, float radius);
			void updateVectors();

		private:
			void updatePosition();
			void updateDirection();

			shapes::Sphere sphere{};
			CelestialBodyParams celestial_body_params;
	};
}

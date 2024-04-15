#pragma once

#include "Camera.hpp"
#include "Program.hpp"
#include "planetary-system/CelestialBody.hpp"

#include <vector>


namespace planetary_system {
	class PlanetarySystem {
		public:
			PlanetarySystem() = default;

			void draw(const Program& program) const;
			void addCelestialBody(planetary_system::CelestialBody&& celestial_body);
			void updateCelestialBodiesVectors();

		private:
			std::vector<planetary_system::CelestialBody> celestial_bodies;
	};
}

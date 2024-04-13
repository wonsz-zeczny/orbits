#pragma once

#include "planetary-system/CelestialBody.hpp"

#include <vector>


class PlanetarySystem {
	public:
		PlanetarySystem() = default;

		void draw() const;
		void addCelestialBody(CelestialBody&& celestial_body);

	private:
		std::vector<CelestialBody> celestial_bodies;
};
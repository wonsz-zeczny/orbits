#pragma once

#include "planetary-system/Planet.hpp"

#include <vector>


class PlanetarySystem {
	public:
		PlanetarySystem() = default;

		void draw() const;
		void addPlanet();

	private:
		std::vector<Planet> planets;
};
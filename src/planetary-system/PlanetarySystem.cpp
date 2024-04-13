#include "planetary-system/PlanetarySystem.hpp"


void PlanetarySystem::draw() const {

}

void PlanetarySystem::addCelestialBody(CelestialBody&& celestial_body) {
	celestial_bodies.push_back(std::move(celestial_body));
}
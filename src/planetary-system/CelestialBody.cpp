#include "planetary-system/CelestialBody.hpp"


using namespace planetary_system;

CelestialBody::CelestialBody(CelestialBodyParams&& celestial_body_params) 
	: celestial_body_params{ std::move(celestial_body_params) } {}

void CelestialBody::draw() const {
	sphere.draw();
}

void CelestialBody::drawLines() const {
	sphere.drawLinesOnSphere();
}

void CelestialBody::configureSphereGeometry(unsigned int stack_count, unsigned int sector_count, float radius) {
	sphere.configureGeometry(stack_count, sector_count, radius);
}
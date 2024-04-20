#include "planetary-system/CelestialBody.hpp"


using namespace planetary_system;


CelestialBody::CelestialBody(CelestialBodyParams&& celestial_body_params) 
	: celestial_body_params{ std::move(celestial_body_params) }, 
	  sphere{ celestial_body_params.texture_filepath, "CelestialBodyTexture", std::move(celestial_body_params.shape_orientation_data)} {
	updateVectors();
	sphere.calculateVertices();
}

void CelestialBody::draw() const {
	sphere.draw();
}

void CelestialBody::drawLines() const {
	sphere.drawLinesOnSphere();
}

void CelestialBody::updateVectors() {
	updatePosition();
	updateDirection();
}

void CelestialBody::configureSphereGeometry(unsigned int stack_count, unsigned int sector_count, float radius) {
	sphere.configureGeometry(stack_count, sector_count, radius);
}

glm::vec3 CelestialBody::getPosition() const {
	return sphere.getPosition();
}

glm::vec3 CelestialBody::getDirection() const {
	return celestial_body_params.shape_orientation_data.position;
}

void CelestialBody::updatePosition() {
	celestial_body_params.shape_orientation_data.position.z = celestial_body_params.distance_from_star_au;
}

void CelestialBody::updateDirection() {
	
}
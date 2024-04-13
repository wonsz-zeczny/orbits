#include "planetary-system/Planet.hpp"


void Planet::draw() const {
	sphere.draw();
}

void Planet::drawWithGrid() const {
	sphere.draw();
	sphere.drawLinesOnSphere();
}

void Planet::configureSphereGeometry(unsigned int stack_count, unsigned int sector_count, float radius) {
	sphere.configureGeometry(stack_count, sector_count, radius);
}
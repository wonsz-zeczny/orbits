#pragma once

#include "shapes/Sphere.hpp"


class Planet {
	public:
		Planet() = default;

		void draw() const;
		void drawWithGrid() const;
		void configureSphereGeometry(unsigned int stack_count, unsigned int sector_count, float radius);

	private:
		shapes::Sphere sphere;
};
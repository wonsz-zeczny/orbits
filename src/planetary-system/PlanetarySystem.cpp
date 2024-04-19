#include "planetary-system/PlanetarySystem.hpp"

#include <glm/gtc/matrix_transform.hpp>


using namespace planetary_system;


void PlanetarySystem::draw(const Program& program) const {
	glm::mat4 view{ camera::Camera::getLookAtMatrix() };

	glm::mat4 projection{ glm::perspective(glm::radians(camera::Camera::getZoom()),
		utils::SCREEN_WIDTH / utils::SCREEN_HEIGHT, 0.1f, 100.0f) };

	program.use();

	program.setMatrix4fv("view", view);
	program.setMatrix4fv("projection", projection);

	for (const auto& celestial_body : celestial_bodies) {
		glm::mat4 model{ glm::mat4{ 1.0f } };
		model = glm::translate(model, glm::vec3{ 0.0f, 0.0f, 
							   celestial_body.getPosition().z * distance_factor});

		program.setMatrix4fv("model", model);

		celestial_body.draw();
	}
}

void PlanetarySystem::addCelestialBody(planetary_system::CelestialBody&& celestial_body) {
	celestial_bodies.push_back(std::move(celestial_body));
}

void PlanetarySystem::updateCelestialBodiesVectors() {
	for (auto& celestial_body : celestial_bodies) {
		celestial_body.updateVectors();
	}
}
#include "planet.hpp"
#include <iostream>

Planet::Planet(Mesh* mesh, Material* material, const glm::vec3& position)
	: Entity(Transform{.position=position}, mesh, material) 
{}

void Planet::update(float deltaTime)
{
	// TODO: Implement planet specific update logic
}

void Planet::render(Shader& shader)
{
	shader.setMat4("model", transform.getModelMatrix());

	shader.setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
	shader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));

	if (!mesh || !material) return;

	mesh->render();
}

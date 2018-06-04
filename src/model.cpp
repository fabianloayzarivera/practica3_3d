#include "model.h"

Model::Model(const std::shared_ptr<Mesh>& mesh) 
{
	this->mesh = mesh;
}

void Model::draw() 
{
	glm::mat4 model(1.0f);
	model = glm::translate(glm::mat4(1.0f), this->getPosition());
	model = glm::rotate(model, this->getRotation().x, glm::vec3(1, 0, 0));
	model = glm::rotate(model, this->getRotation().y, glm::vec3(0, 1, 0));
	model = glm::rotate(model, this->getRotation().z, glm::vec3(0, 0, 1));
	model = glm::scale(model, this->getScale());

	State::modelMatrix = model;
	mesh->draw();
}
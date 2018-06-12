#include "model.h"

Model::Model(const std::shared_ptr<Mesh>& mesh) 
{
	this->mesh = mesh;
}

void Model::draw() 
{
	glm::mat4 model(1.0f);
	model = glm::translate(glm::mat4(1.0f), this->getPosition());
	glm::quat quaternion(this->getRotation());
	model = glm::rotate(glm::mat4(1.0f), glm::angle(quaternion), glm::axis(quaternion));
	model = glm::scale(model, this->getScale());

	State::modelMatrix = model;
	mesh->draw();
}
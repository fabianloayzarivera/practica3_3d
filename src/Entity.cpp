#include "Entity.h"

Entity::Entity() 
{
	this->setPosition(glm::vec3(0, 0, 0));
	this->setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	this->setScale(glm::vec3(0, 0, 0));
}

void Entity::move(const glm::vec3& vec) 
{
	position += rotation * vec;
}
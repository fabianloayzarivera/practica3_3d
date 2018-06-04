#pragma once
#include "common.h"

class Entity 
{
private:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

public:
	Entity();
	virtual ~Entity() {}

	const glm::vec3&	getPosition() const { return position; }
	void				setPosition(const glm::vec3& pos) { position = pos; }
	const				glm::vec3& getRotation() const { return rotation; }	// puede ser quat
	const				glm::vec3& getRotationEuler() const { return glm::degrees(rotation); }
	const void			setRotation(const glm::vec3& rot) {rotation = glm::radians(rot); }// puede ser quat
	const glm::vec3&	getScale() const { return scale; }
	void				setScale(const glm::vec3& scale) { this->scale = scale; }
	void				move(const glm::vec3& vec); // ver en las diapositivas
	virtual void		update(float deltaTime) {}
	virtual void		draw() {}

};
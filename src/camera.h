#pragma once
#include "common.h"
#include "Entity.h"
#include "state.h"

class Camera : public Entity
{
private:
	glm::mat4 projection;
	glm::ivec4 viewport;
	glm::vec3 color;
public:

	Camera(const float& fovy, const float& width, const float& height, const float& near, const float& far);

	const glm::mat4& getProjection() const { return projection; }
	void setProjection(const glm::mat4& proj) { projection = proj; }

	const glm::ivec4& getViewport() const { return viewport; }
	void setViewport(const glm::ivec4& vp) { viewport = vp; }

	const glm::vec3& getClearColor() const { return color; }
	void setClearColor(const glm::vec3& color) { this->color = color; }

	void prepare();

};
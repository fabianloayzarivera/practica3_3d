#include "camera.h"

Camera::Camera(const float& fovy, const float& width, const float& height, const float& near, const float& far)
{
	projection = glm::perspective(glm::radians(fovy), (width / height), near, far);

}

void Camera::prepare() 
{
	State::projectionMatrix = this->getProjection();
	glm::mat4 view = glm::mat4();
	
	glm::quat quaternion(this->getRotation());
	view = glm::rotate(glm::mat4(1.0f), glm::angle(quaternion) *-1, glm::axis(quaternion));
	view = glm::translate(view, this->getPosition() * -1.0f);
	State::viewMatrix = view;

	glViewport(viewport.x, viewport.y, viewport.z, viewport.w);
	glScissor(viewport.x, viewport.y, viewport.z, viewport.w);


	glClearColor(color.x, color.y, color.z, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
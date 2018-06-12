#include "material.h"
#include "state.h"

Material::Material(const std::shared_ptr<Texture>& tex , const std::shared_ptr<Shader>& _shader)
{	
	shader = _shader;
	texture = tex;
}

void Material::prepare() 
{
	this->getShader()->use();
	
	glm::mat4 MVP = State::projectionMatrix * State::viewMatrix * State::modelMatrix;

	this->getShader()->setMatrix(this->getShader()->getLocation("MVP"), MVP);
	this->getShader()->setInt(this->getShader()->getLocation("texSampler"), 0);
	if (texture)
		glBindTexture(GL_TEXTURE_2D, texture->getId());
}
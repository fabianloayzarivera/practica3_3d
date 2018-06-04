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
	glUniform1i(this->getShader()->getLocation("texSampler"), 0);
	//NEW UNIFORM VARIABLES???
	if (texture)
		glBindTexture(GL_TEXTURE_2D, texture->getId());
}
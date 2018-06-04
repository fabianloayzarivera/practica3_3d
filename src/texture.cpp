#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

Texture::Texture(const uint32_t& _id, const glm::ivec2& _size) 
{
	texId	= _id;
	size	= _size;
}

Texture::~Texture() 
{
	//DESTROY TEXTURES
}

std::shared_ptr<Texture> Texture::load(const char* filename, int *width, int *height)
{
	

	unsigned char* buffer = stbi_load(filename, width, height, nullptr, 4);

	if (buffer == NULL) {
		return nullptr;
	}
	
	GLuint id;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, *width, *height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);	
	glGenerateMipmap(GL_TEXTURE_2D);		std::shared_ptr<Texture> tex(new Texture(id, glm::ivec2(*width, *height)));	stbi_image_free(buffer);

	return tex;
	


}
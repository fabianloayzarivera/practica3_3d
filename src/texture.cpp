#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

//Texture::Texture(const uint32_t& _id, const glm::ivec2& _size) 
//{
//	texId	= _id;
//	size	= _size;
//}

Texture::Texture()
{
}


std::shared_ptr<Texture> Texture::load(const char* filename)
{
	std::shared_ptr<Texture> tex(new Texture(), [](Texture *p) {delete p; });
	unsigned char* buffer = stbi_load(filename, &tex->size.x, &tex->size.y, nullptr, 4);

	if (buffer == NULL) {
		return nullptr;
	}
	
	glGenTextures(1, &tex->texId);
	glBindTexture(GL_TEXTURE_2D, tex->texId);
	glTexParameteri(GL_TEXTURE_2D, GL_LINEAR_MIPMAP_LINEAR, GL_TEXTURE_MIN_FILTER);
	stbi_set_flip_vertically_on_load(true);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->size.x, tex->size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
	glGenerateMipmap(GL_TEXTURE_2D);		stbi_image_free(buffer);

	return tex;

}

void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, texId); 
}
#pragma once
#include "common.h"

class Texture 
{
private:
	uint32_t	texId;
	glm::ivec2	size;
public:
	//Texture(const uint32_t& _id, const glm::ivec2& _size);
	Texture();
	static std::shared_ptr<Texture>	load(const char* filename);
	uint32_t						getId() const { return texId; }
	void							setId(uint32_t _id) { texId = _id; }
	const glm::ivec2&				getSize() const { return size; }
	void							setSize(glm::ivec2 _size) { size = _size; }
	void							bind() const;

};
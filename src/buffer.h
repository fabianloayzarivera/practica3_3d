#pragma once
#include "common.h"
#include <vector>
#include "vertex.h"

class Shader;
class Buffer 
{
private:
	uint32_t vertexBuffer;
	uint32_t indexBuffer;

	std::vector<Vertex> vertices;
	std::vector <uint16_t> indexes;
public:
	Buffer(std::vector<Vertex> v, std::vector<uint16_t> i);
	~Buffer();
	void draw(const Shader& shader) const;
};
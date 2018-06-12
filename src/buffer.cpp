
#include "buffer.h"
#include "shader.h"
Buffer::Buffer(std::vector<Vertex> vertex, std::vector<uint16_t> _indexes) 
{
	vertices = vertex;
	indexes = _indexes;
	//VERTEX	
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertex.size(), vertex.data(), GL_STATIC_DRAW);

	//INDEXES
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * indexes.size(), indexes.data(), GL_STATIC_DRAW);


}

void Buffer::draw(const Shader& shader) const 
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	shader.setupAttribs();
	glDrawElements(GL_TRIANGLES, indexes.size(), GL_UNSIGNED_SHORT, nullptr);
}

Buffer::~Buffer() 
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
}
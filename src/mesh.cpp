#include "mesh.h"

void Mesh::addBuffer(const std::shared_ptr<Buffer>& buffer, const Material& _material)
{
	buffers.push_back(std::pair<std::shared_ptr<Buffer>, Material>(buffer, _material));
}

size_t Mesh::getNumBuffers() const 
{
	return buffers.size();
}

const std::shared_ptr<Buffer>& Mesh::getBuffer(size_t index) const 
{
	return buffers.at(index).first;
}

std::shared_ptr<Buffer>& Mesh::getBuffer(size_t index)
{
	return buffers.at(index).first;
}

void Mesh::draw() 
{
	for (auto pairIt = buffers.begin(); pairIt != buffers.end(); ++pairIt) {
		std::shared_ptr<Buffer> buff = pairIt->first;
		Material &m = pairIt->second;
		m.prepare();
		buff->draw(*m.getShader());
	}
}
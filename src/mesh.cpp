#include "mesh.h"

void Mesh::addBuffer(const std::shared_ptr<Buffer>& buffer, const std::shared_ptr<Shader>& shader) 
{
	buffers.push_back(std::pair<std::shared_ptr<Buffer>, std::shared_ptr<Shader>>(buffer, shader));
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
		
		glm::mat4 mvp = glm::mat4();
		mvp = State::projectionMatrix * State::viewMatrix * State::modelMatrix;
		State::defaultShader->setMatrix(State::defaultShader->getLocation("mvp"), mvp);

		if ((*pairIt).second != nullptr){
			(*pairIt).second->use();
			(*pairIt).first->draw(*((*pairIt).second));
		}
		else {
			State::defaultShader->use();
			(*pairIt).first->draw(*State::defaultShader);
		}
		
	}
}
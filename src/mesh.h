#pragma once
#include "common.h"
#include "shader.h"
#include "state.h"
#include "buffer.h"


class Mesh 
{
private:
	std::vector<std::pair<std::shared_ptr<Buffer>, std::shared_ptr<Shader>>> buffers;
	
public:
	void addBuffer(const std::shared_ptr<Buffer>& buffer, const std::shared_ptr<Shader>& shader = nullptr);
	size_t getNumBuffers() const;
	const std::shared_ptr<Buffer>& getBuffer(size_t index) const;
	std::shared_ptr<Buffer>& getBuffer(size_t index);
	void draw();

};
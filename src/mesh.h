#pragma once
#include "common.h"
#include "shader.h"
#include "state.h"
#include "buffer.h"
#include "material.h"


class Mesh 
{
private:
	std::vector<std::pair<std::shared_ptr<Buffer>, Material>> buffers;
	
public:
	void addBuffer(const std::shared_ptr<Buffer>& buffer, const Material& _material);
	const Material& getMaterial(size_t index) const { return buffers[index].second; }
	Material& getMaterial(size_t index) { return buffers[index].second; }

	size_t getNumBuffers() const;
	const std::shared_ptr<Buffer>& getBuffer(size_t index) const;
	std::shared_ptr<Buffer>& getBuffer(size_t index);
	void draw();

};
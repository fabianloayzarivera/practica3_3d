#pragma once
#include "common.h"
#include <vector>
#include "Entity.h"
#include "camera.h"

class World 
{
private:
	std::vector<std::shared_ptr<Entity>> entities;
	std::vector<std::shared_ptr<Camera>> cameras;
public:
	void addEntity(const std::shared_ptr<Entity>& entity);
	void removeEntity(const std::shared_ptr<Entity>& entity);
	size_t getNumEntities() const { return entities.size(); }
	const std::shared_ptr<Entity>& getEntity(size_t index) const { return entities.at(index); }
	std::shared_ptr<Entity>& getEntity(size_t index) { return entities.at(index); }
	void update(float deltaTime);
	void draw();

};
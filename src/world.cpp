#include "world.h"

void World::addEntity(const std::shared_ptr<Entity>& entity) 
{
	std::shared_ptr<Camera> camera = std::dynamic_pointer_cast<Camera>(entity);
	if (camera)
		cameras.push_back(camera);

	entities.push_back(entity);
}

void World::removeEntity(const std::shared_ptr<Entity>& entity) 
{
	//DO SOMETHING
}

void World::update(float deltaTime) 
{
	for (auto It = entities.begin(); It != entities.end(); ++It) {
		(*It)->update(deltaTime);
	}
}

void World::draw() 
{
	for (auto It = cameras.begin(); It != cameras.end(); ++It) {
		
		(*It)->prepare();
		for (auto ItEntity = entities.begin(); ItEntity != entities.end(); ++ItEntity) {
			(*ItEntity)->draw();
		}
	}
}
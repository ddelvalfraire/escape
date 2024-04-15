#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include <vector>

#include "Entity.h"

class EntityFactory
{
public:
	static EntityFactory& getInstance();
	Entity* createPlayer();

private:
	EntityFactory() = default;
	EntityFactory(EntityFactory&) = delete;
	void operator=(EntityFactory const&) = delete;

};
#endif // !ENTITY_FACTORY_H


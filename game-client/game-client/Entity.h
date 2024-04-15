#ifndef ENTITY_H
#define ENTITY_H

#include <unordered_map>
#include <typeinfo>
#include <stdexcept>
#include <memory>
#include <utility>

#include "Component.h"
#include "TypeMap.h"

/**
 * @brief Entity container for the ECS
 * 
 */
class Entity : public TypeMap<Component>
{
	friend class EntityFactory;
private:
	Entity() = default;
};

#endif // !ENTITY_H

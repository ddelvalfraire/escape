#ifndef VELOCITY_COMPONENT_H
#define VELOCITY_COMPONENT_H

#include <SFML/System.hpp>

#include "Component.h"

/**
 * @brief represents the velocity of an entity
 * 
 */
struct VelocityComponent : public sf::Vector2f, Component
{
	VelocityComponent(float x = 0.0f, float y = 0.0f) : sf::Vector2f(x, y) {}
};

#endif // !VELOCITY_COMPONENT_H

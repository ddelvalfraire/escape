#ifndef POSITION_COMPONENT_H
#define POSITION_COMPONENT_H

#include <SFML/System.hpp>

#include "Component.h"

/**
 * @brief Position component represents the x,y coordinates of an entity in a window
 * 
 */
struct PositionComponent : public sf::Vector2f, Component
{
	PositionComponent(float x = 0, float y = 0) : sf::Vector2f(x, y) {}
};

#endif // !POSITION_COMPONENT_H
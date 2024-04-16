#ifndef COMPONENT_H
#define COMPONENT_H

#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Item.h"
#include "TypeMap.h"

/**
 * @brief abstract component for the ECS
 * 
 */
class Component 
{
public:
	virtual ~Component() = default;
};

/**
 * @brief Inventory management system for entities
 *
 */
struct Inventory : public TypeMap<Item> , Component
{
};

/**
 * @brief Represents the various states of movement in an entity
 *
 */
struct MovementStateComponent : Component
{
	MovementStateComponent(bool isFalling = false, bool isJumping = false, bool isCrouched = false)
		:isFalling(isFalling), isJumping(isJumping), isCrouched(isCrouched) {}

	bool isFalling;
	bool isJumping;
	bool isCrouched;
};

/**
 * @brief Position component represents the x,y coordinates of an entity in a window
 *
 */
struct PositionComponent : public sf::Vector2f, Component
{
	PositionComponent(float x = 0, float y = 0) : sf::Vector2f(x, y) {}
	PositionComponent(sf::Vector2f& vec) : sf::Vector2f(vec) {}
	PositionComponent(const sf::Vector2f& vec) : sf::Vector2f(vec) {}
};

/**
 * @brief represents the velocity of an entity
 *
 */
struct VelocityComponent : public sf::Vector2f, Component
{
	VelocityComponent(float x = 0.0f, float y = 0.0f) : sf::Vector2f(x, y) {}
	VelocityComponent(sf::Vector2f& vec) : sf::Vector2f(vec) {}
	VelocityComponent(const sf::Vector2f& vec) : sf::Vector2f(vec) {}
};

/**
 * @brief represents the state of a lever
 *
 */
struct LeverStateComponent : Component
{
	LeverStateComponent(bool isOn) : isOn(isOn) {}
	bool isOn;
};

/**
 * @brief stores the sprite and animation data of an entity
 *
 */
struct GraphicComponent : Component
{
	std::vector<sf::IntRect> frames;
	sf::Texture& spriteTexture;
	sf::Sprite sprite;


};


#endif // !COMPONENT_H

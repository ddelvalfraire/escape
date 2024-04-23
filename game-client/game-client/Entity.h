#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <Box2d/Box2d.h>

#include "Entity.h"

constexpr auto DENSITY = 1.0f;
constexpr auto FRICTION = 0.3f;
constexpr auto B2_SF_SCALE = 30.0f;

class Entity
{
public:
	Entity(
		sf::FloatRect rect,
		b2World& physicsWorld,
		b2BodyType physicsType,
		bool centerOrigin = false,
		sf::Texture* texture = nullptr,
		sf::Color color = sf::Color::Red,
		float scalar = 1.0f
	);

	virtual ~Entity();
	virtual void update(sf::Time dt);
	void setPhysicsBodyPtr(Entity* ptr);
	void syncPositions();
	b2Body* physicsBody();
	sf::Drawable* sprite();

protected:
	Entity();
	void initEntityFromAnimation(sf::IntRect& frame, sf::Texture* texture, sf::Vector2f position, b2World& world, float scalar);
	b2Body* initPhysicsBody(sf::IntRect& physicsRect, b2World& physicsWorld, b2BodyType physicsType, float scalar, bool isSensor = false);
	sf::Drawable* initDrawable(const sf::IntRect& textRect, const sf::Texture* texture, const sf::Vector2f& position, bool centerOrigin, float scalar);
	sf::Drawable* initDrawable(const sf::IntRect& textRect, bool centerOrigin, const sf::Texture* texture, const sf::Vector2f position, sf::Color color, float scalar);
	void sprite(sf::Sprite* sprite);

	b2Body* mpPhysicsBody;
	sf::Drawable* mpSprite;
};

#endif // !ENTITY_H

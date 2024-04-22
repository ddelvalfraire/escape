#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <Box2d/Box2d.h>

constexpr auto DENSITY = 1.0f;
constexpr auto FRICTION = 0.3f;
constexpr auto B2_SF_SCALE = 30.0f;

class Entity
{
public:
	Entity(
		sf::IntRect rect,
		b2World& physicsWorld,
		b2BodyType physicsType,
		sf::Color color = sf::Color::Transparent
	);

	Entity(
		sf::IntRect textRect,
		b2World& physicsWorld,
		b2BodyType physicsType,
		bool centerOrigin,
		sf::Texture* texture = nullptr,
		sf::Vector2f position = { 0.0, 0.0 },
		sf::Color color = sf::Color::Transparent,
		float scalar = 1.0f
	);

	~Entity();

	void syncPositions();

	b2Body* physicsBody();
	sf::Drawable* sprite();

protected:
	Entity();
	b2Body* initPhysicsBody(sf::IntRect& physicsRect, b2World& physicsWorld, b2BodyType physicsType, float scalar );
	sf::Drawable* initDrawable(const sf::IntRect& textRect, const sf::Texture* texture, const sf::Vector2f& position, bool centerOrigin, float scalar);
	sf::Drawable* initDrawable(const sf::IntRect& textRect, bool centerOrigin, const sf::Texture* texture, const sf::Vector2f position, sf::Color color, float scalar);
	void sprite(sf::Sprite* sprite);

	b2Body* mpPhysicsBody;
	sf::Drawable* mpDrawable;
};

#endif // !ENTITY_H

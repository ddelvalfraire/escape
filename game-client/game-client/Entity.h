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
		sf::FloatRect rect,
		b2World& physicsWorld,
		b2BodyType physicsType,
		bool centerOrigin = false,
		sf::Texture* texture = nullptr,
		sf::Color color = sf::Color::Red,
		float scalar = 1.0f
	);
	~Entity();

	void syncPositions();

	b2Body* physicsBody();
	sf::Drawable* sprite();

protected:
	Entity();
	b2Body* initPhysicsBody(sf::FloatRect& rect, b2World& physicsWorld, b2BodyType physicsType, float scalar = 1);
	sf::Drawable* initSprite(sf::FloatRect& rect, bool centerOrigin, sf::Texture* texture, sf::Color color = sf::Color::Red , float scalar = 1);
	void sprite(sf::Sprite* sprite);

	b2Body* mpPhysicsBody;
	sf::Drawable* mpSprite;
};

#endif // !ENTITY_H

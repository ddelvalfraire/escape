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
	Entity(sf::FloatRect rect, b2World& physicsWorld, b2BodyType physicsType,bool centerOrigin = false, sf::Texture* texture = nullptr, sf::Color color = sf::Color::White);
	~Entity();

	void updatePosition();

	b2Body* physicsBody();
	sf::Drawable* sprite();
	bool isJumping();
	void isJumping(bool flag);
	bool isInteracting();
	void isInteracting(bool flag);

private:
	b2Body* initPhysicsBody(sf::FloatRect& rect, b2World& physicsWorld, b2BodyType physicsType);
	sf::Drawable* initSprite(sf::FloatRect& rect, bool centerOrigin, sf::Texture* texture, sf::Color color);

	b2Body* mpPhysicsBody;
	sf::Drawable* mpSprite;
	bool mIsJumping;
	bool mIsInteracting;
};

#endif // !ENTITY_H

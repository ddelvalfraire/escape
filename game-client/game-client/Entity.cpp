#include "Entity.h"

Entity::Entity(
	sf::FloatRect rect,
	b2World& physicsWorld,
	b2BodyType physicsType,
	bool centerOrigin,
	sf::Texture* texture,
	sf::Color color
)
{
	mpPhysicsBody = initPhysicsBody(rect, physicsWorld, physicsType);
	mpSprite = initSprite(rect,centerOrigin, texture, color); // depends on physics body for data, must be called second
}

Entity::~Entity()
{
	delete mpSprite;

	// delete mpPhysicsBody; world owns b2Body objects
}

void Entity::updatePosition()
{
	auto sprite = static_cast<sf::RectangleShape*>(mpSprite);
	sprite->setPosition(
		mpPhysicsBody->GetPosition().x * B2_SF_SCALE,
		mpPhysicsBody->GetPosition().y * B2_SF_SCALE
		);
	
}

b2Body* Entity::physicsBody()
{
	return mpPhysicsBody;
}

sf::Drawable* Entity::sprite()
{
	return mpSprite;
}

bool Entity::isJumping()
{
	return mIsJumping;
}

void Entity::isJumping(bool flag)
{
	mIsJumping = flag;
}
void Entity::isInteracting(bool flag)
{
	mIsInteracting = flag;
}
bool Entity::isInteracting()
{
	return mIsInteracting;
}

b2Body* Entity::initPhysicsBody(sf::FloatRect& rect, b2World& physicsWorld, b2BodyType physicsType)
{
	b2BodyDef bDef; 
	b2FixtureDef fDef; 
	b2PolygonShape shape;

	bDef.position.Set( rect.left / B2_SF_SCALE, rect.top / B2_SF_SCALE);
	shape.SetAsBox( rect.width / 2 / B2_SF_SCALE, rect.height / 2 / B2_SF_SCALE);
	bDef.type = physicsType;
	b2Body* body = physicsWorld.CreateBody(&bDef);
	fDef.shape = &shape;
	fDef.density = DENSITY;
	fDef.friction = FRICTION;
	body->SetFixedRotation(true);
	body->CreateFixture(&fDef);

	return physicsWorld.GetBodyList(); // returns the last inserted body 
}

sf::Drawable* Entity::initSprite(sf::FloatRect& rect, bool centerOrigin, sf::Texture* texture, sf::Color color)
{
	if (!mpPhysicsBody)
		throw std::runtime_error("Physics body not iniitialized");

	if (!texture)
	{
		auto shape = new sf::RectangleShape(rect.getSize());

		if (centerOrigin)
			shape->setOrigin(rect.getSize() / 2.0f);

		shape->setPosition(rect.left - rect.width / 2, rect.top - rect.height / 2);
		shape->setFillColor(color);

		return shape;
	}

	auto sprite = new sf::Sprite();
	sprite->setPosition(rect.left - rect.width / 2, rect.top - rect.height / 2);
	sf::IntRect textureRect(rect);
	sprite->setTexture(*texture);
	sprite->setTextureRect(textureRect);

	return sprite;
}
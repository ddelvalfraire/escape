#include "Entity.h"

Entity::Entity() 
{
}

/**
 * @brief Construct a new Entity:: Entity object
 * 
 * @param rect size and position of the entity to build.
 * @param physicsWorld reference to the physics world
 * @param physicsType type of physics object to create
 * @param centerOrigin flag that sets sprite origin at center when true
 * @param texture sprite texture handle
 * @param color color for the default shape 
 * @param scalar scalar for sprite and physics body
 */
Entity::Entity(
	sf::FloatRect rect,
	b2World& physicsWorld,
	b2BodyType physicsType,
	bool centerOrigin,
	sf::Texture* texture,
	sf::Color color,
	float scalar
)
{
	mpPhysicsBody = initPhysicsBody(rect, physicsWorld, physicsType, scalar);
	mpSprite = initSprite(rect,centerOrigin, texture, color); // depends on physics body for data, must be called second
}

/**
 * @brief Destroy the Entity:: Entity object
 * 
 */
Entity::~Entity()
{
	delete mpSprite;

	// delete mpPhysicsBody; world owns b2Body objects
}

void Entity::syncPositions()
{
	auto sprite = static_cast<sf::RectangleShape*>(mpSprite);
	sprite->setPosition(
		mpPhysicsBody->GetPosition().x * B2_SF_SCALE,
		mpPhysicsBody->GetPosition().y * B2_SF_SCALE
		);
	
}

/**
 * @brief  mpPhysicsBody getter
 * 
 * @return b2Body* handle to the entity physics body
 */
b2Body* Entity::physicsBody()
{
	return mpPhysicsBody;
}

/**
 * @brief mpSprite getter
 * 
 * @return sf::Drawable* reference to the entity drawable
 */
sf::Drawable* Entity::sprite()
{
	return mpSprite;
}

/**
 * @brief mpSprite setter
 * 
 * @param sprite new sprite
 */
void Entity::sprite(sf::Sprite* sprite)
{
	mpSprite = sprite;
}
/**
 * @brief Initializes a physics body
 * 
 * @param rect size and position of the body
 * @param physicsWorld reference to the world to add the body
 * @param physicsType type of body
 * @param scalar body scalar to match sprite scaling
 * @return b2Body* reference to the newly created body
 */
b2Body* Entity::initPhysicsBody(sf::FloatRect& rect, b2World& physicsWorld, b2BodyType physicsType, float scalar)
{
	b2BodyDef bDef; 
	b2FixtureDef fDef; 
	b2PolygonShape shape;

	bDef.position.Set( rect.left / B2_SF_SCALE, rect.top / B2_SF_SCALE);
	
	float sizeX = rect.width / 2 / B2_SF_SCALE * scalar;
	float sizeY = rect.height / 2 / B2_SF_SCALE * scalar;
	shape.SetAsBox( sizeX, sizeY);
	bDef.type = physicsType;
	b2Body* body = physicsWorld.CreateBody(&bDef);
	fDef.shape = &shape;
	fDef.density = DENSITY;
	fDef.friction = FRICTION;
	body->SetFixedRotation(true);
	body->CreateFixture(&fDef);

	return physicsWorld.GetBodyList(); // returns the address of last inserted body 
}

/**
 * @brief initializes the entity drawable
 * 
 * @param rect size and position of the drawable
 * @param centerOrigin if true centers sprite origin
 * @param texture handle to sprite texture
 * @param color color for default rectangle
 * @param scalar sprite scalar
 * @return sf::Drawable* 
 */
sf::Drawable* Entity::initSprite(sf::FloatRect& rect, bool centerOrigin, sf::Texture* texture,sf::Color color, float scalar)
{
	if (!mpPhysicsBody)
		throw std::runtime_error("Physics body not iniitialized");

	if (!texture) // default squares
	{
		auto shape = new sf::RectangleShape(rect.getSize());

		if (centerOrigin)
			shape->setOrigin(rect.getSize() / 2.0f);

		shape->setPosition(rect.left - rect.width / 2, rect.top - rect.height / 2);
		shape->setScale(scalar, scalar);
		shape->setFillColor(color);

		return shape;
	}

	auto sprite = new sf::Sprite(*texture, sf::IntRect(rect));
	sprite->setPosition(rect.left - rect.width / 2, rect.top - rect.height / 2);
	
	if (centerOrigin)
		sprite->setOrigin(rect.getSize() / 2.0F);

	sprite->setScale(scalar, scalar);

	return sprite;
}


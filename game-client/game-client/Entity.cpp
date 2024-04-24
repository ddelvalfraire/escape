#include "Entity.h"

/**
 * @brief Construct a new Entity:: Entity object
 * 
 */
Entity::Entity() 
{
}

/**
 * @brief sets the user data pointer of a physics body
 * 
 * @param ptr 
 */
void Entity::setPhysicsBodyPtr(Entity* ptr)
{
	mpPhysicsBody->GetUserData().pointer = reinterpret_cast<uintptr_t>(ptr);
}

/**
 * @brief Construct a new Entity:: Entity object
 * 
 * @param rect size and position of the drawable texture.
 * @param physicsWorld reference to the physics world
 * @param physicsType type of physics object to create
 * @param color color for the default shape 
 */
Entity::Entity(sf::IntRect rect, b2World& physicsWorld, b2BodyType physicsType, sf::Color color)
	: Entity(rect, physicsWorld, physicsType, false, nullptr, { 0,0 }, color)
{
	mpPhysicsBody = initPhysicsBody(rect, physicsWorld, physicsType, 1);
	mpDrawable = initDrawable(rect, false, nullptr, {0,0}, color, 1); // depends on physics body for data, must be called second
}

/**
 * @brief Construct a new Entity:: Entity object
 * 
 * @param textRect size and position of the drawable texture.
 * @param position position of the sprite and physics body
 * @param physicsWorld reference to the physics world
 * @param physicsType type of physics object to create
 * @param centerOrigin flag that sets sprite origin at center when true
 * @param texture sprite texture handle
 * @param color color for the default shape 
 * @param scalar scalar for sprite and physics body
 */
Entity::Entity(
	sf::IntRect textRect,
	b2World& physicsWorld,
	b2BodyType physicsType,
	bool centerOrigin,
	sf::Texture* texture,
	sf::Vector2f position,
	sf::Color color,
	float scalar
)
{
	sf::Vector2i intPos = static_cast<sf::Vector2i>(position);
	sf::IntRect physicsRect(intPos, textRect.getSize());
	mpPhysicsBody = initPhysicsBody(physicsRect, physicsWorld, physicsType, scalar);
	mpDrawable = initDrawable(textRect, centerOrigin, texture, position, color, scalar); // depends on physics body for data, must be called second

}

/**
 * @brief creates an entity from a frame animation and texture
 * 
 * @param frame beginning animation frame
 * @param texture animation texture
 * @param position unscaled x, y coordinates to spawn the entity
 * @param world physics world reference
 * @param scalar physics and drawable scalar
 */
void Entity::initEntityFromAnimation(sf::IntRect& frame, sf::Texture* texture, sf::Vector2f position, b2World& world, float scalar )
{
	const int x = position.x, y = position.y;
	sf::IntRect physicsRect({ x, y }, frame.getSize());

	mpPhysicsBody = initPhysicsBody(physicsRect, world, b2_dynamicBody, scalar);
	mpDrawable = initDrawable(frame, texture, position, true, scalar);
}
/**
 * @brief Destroy the Entity:: Entity object
 * 
 */
Entity::~Entity()
{
	delete mpDrawable;

	// delete mpPhysicsBody; world owns b2Body objects
}

/**
 * @brief default update function
 * 
 * @param dt elapsed time
 */
void Entity::update(sf::Time dt)
{
}


/**
 * @brief syncs the position of a physics body and a transformable(usually sprite)
 * 
 */
void Entity::syncPositions()
{
	auto sprite = static_cast<sf::RectangleShape*>(mpDrawable);
	const auto x = mpPhysicsBody->GetPosition().x * B2_SF_SCALE;
	const auto y = mpPhysicsBody->GetPosition().y * B2_SF_SCALE;
	sprite->setPosition(x, y);
	
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
 * @brief mpDrawable getter
 * 
 * @return sf::Drawable* reference to the entity drawable
 */
sf::Drawable* Entity::sprite()
{
	return mpDrawable;
}

/**
 * @brief mpDrawable setter
 * 
 * @param sprite new sprite
 */
void Entity::sprite(sf::Sprite* sprite)
{
	mpDrawable = sprite;
}
/**
 * @brief Initializes a physics body
 * 
 * @param physicsRect size and position of the body
 * @param physicsWorld reference to the world to add the body
 * @param physicsType type of body
 * @param scalar body scalar to match sprite scaling
 * @return b2Body* reference to the newly created body
 */
b2Body* Entity::initPhysicsBody(sf::IntRect& physicsRect, b2World& physicsWorld, b2BodyType physicsType, float scalar, bool isSensor)
{
	b2BodyDef bDef; 
	b2FixtureDef fDef; 
	b2PolygonShape shape;

	bDef.position.Set(physicsRect.left / B2_SF_SCALE, physicsRect.top / B2_SF_SCALE);
	
	float sizeX = physicsRect.width / 2 / B2_SF_SCALE * scalar;
	float sizeY = physicsRect.height / 2 / B2_SF_SCALE * scalar;

	shape.SetAsBox( sizeX, sizeY);
	bDef.type = physicsType;
	b2Body* body = physicsWorld.CreateBody(&bDef);
	fDef.isSensor = isSensor;
	fDef.shape = &shape;
	fDef.density = DENSITY;
	fDef.friction = FRICTION;
	body->SetFixedRotation(true);
	body->CreateFixture(&fDef);

	return physicsWorld.GetBodyList(); // returns the address of last inserted body 
}

sf::Drawable* Entity::initDrawable(const sf::IntRect& textRect,const sf::Texture* texture, const sf::Vector2f& position, bool centerOrigin, float scalar)
{
	return initDrawable(textRect, centerOrigin, texture, position, sf::Color::Transparent, scalar);
}

/**
 * @brief initializes the entity drawable
 * 
 * @param textRect size and position of the texture
 * @param position position of the drawable
 * @param centerOrigin if true centers sprite origin
 * @param texture handle to sprite texture
 * @param color color for default rectangle
 * @param scalar sprite scalar
 * @return sf::Drawable* 
 */
sf::Drawable* Entity::initDrawable(const sf::IntRect& textRect, bool centerOrigin, const sf::Texture* texture, const sf::Vector2f position, sf::Color color, float scalar)
{
	if (!mpPhysicsBody)
		throw std::runtime_error("Physics body not iniitialized");

	const auto floatRect = static_cast<sf::FloatRect>(textRect);

	if (!texture) // default squares
	{
		auto shape = new sf::RectangleShape(floatRect.getSize());

		if (centerOrigin)
			shape->setOrigin(floatRect.getSize() / 2.0f);

		shape->setPosition(textRect.left - textRect.width / 2, textRect.top - textRect.height / 2);
		shape->setScale(scalar, scalar);
		shape->setFillColor(color);

		return shape;
	}

	auto sprite = new sf::Sprite(*texture, textRect);

	if (centerOrigin)
		sprite->setOrigin(floatRect.getSize() / 2.0F);

	sprite->setPosition(position.x - textRect.width / 2 * scalar, position.y - textRect.height / 2 * scalar);
	
	sprite->setScale(scalar, scalar);

	return sprite;
}


#include <box2d/box2d.h>
#include "Lever.h"

constexpr auto SCALAR = 2.0F;
constexpr auto LEVER_OFF = "Entities/lever1.png";
constexpr auto LEVER_ON = "lever2.png";

//constructor for Lever object
Lever::Lever(sf::Vector2f position, TextureManager& textureManager, b2World& physicsWorld)
	: Entity(), mTextureManager(textureManager), mWorld(physicsWorld)
{
	sf::Texture* leverTexture;
	if (mTextureManager.hasTexture(LEVER_OFF))
		leverTexture = mTextureManager.getTexture(LEVER_OFF);
	else
		leverTexture = mTextureManager.loadTexture(LEVER_OFF); 

	sf::FloatRect textureRect({ 0, 0, 64, 64 });

	sf::FloatRect physicsPosition({position.x, position.y, textureRect.width, textureRect.height});
	
	mpPhysicsBody = initPhysicsBody(physicsPosition, physicsWorld, b2_staticBody, SCALAR);
	mpSprite = initSprite(textureRect, true, leverTexture, sf::Color::Red, SCALAR);

	auto leverSprite = static_cast<sf::Sprite*>(mpSprite);		//create sprite object for lever
	leverSprite->setPosition(position);
}
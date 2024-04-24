#include "Emerald.h"

const std::string FILE_PATH = "Entities/Gems/";
const auto GEM_3 = "3.png";

/**
 * @brief Construct a new Emerald:: Emerald object
 * 
 * @param position unscaled x, y coordinate to place the emerald
 * @param resourceContainer ResourceContainer reference
 */
Emerald::Emerald(sf::Vector2f position, ResourceContainer& resourceContainer)
	:Emerald(position, resourceContainer.textureManager(), resourceContainer.world())
{
}

/**
 * @brief Construct a new Emerald:: Emerald object
 * 
 * @param position 
 * @param textureManager 
 * @param physicsWorld 
 */
Emerald::Emerald(sf::Vector2f position, TextureManager& textureManager, b2World& physicsWorld)
	:Entity(), Animatable(textureManager) 
{
	const auto EMERALD_SCALAR = 2.0F;
	
	loadAnimations();
	setAnimation(FILE_PATH + GEM_3);

	sf::IntRect& frame = mCurrentAnimation->frames[mCurrentFrame];
	sf::Texture* tex = mTextureManager.getTexture(mCurrentAnimation->textureKey);

	const int x = position.x, y = position.y;
	sf::IntRect physicsRect({ x, y }, frame.getSize());

	mpPhysicsBody = initPhysicsBody(physicsRect, physicsWorld, b2_staticBody, EMERALD_SCALAR, true);
	mpDrawable = initDrawable(frame, tex, position, false, EMERALD_SCALAR);

}

void Emerald::update(sf::Time dt)
{
	updateAnimation(dt, mpDrawable);
}


void Emerald::loadAnimations()
{
	sf::Vector2i sizeInPixels(16, 16);
	loadAnimation(FILE_PATH + GEM_3, 7, 0.08f, sizeInPixels);
}


#include "Emerald.h"

const std::string FILE_PATH = "Entities/Gems/";
const auto GEM_3 = "3.png";

Emerald::Emerald(sf::Vector2f position, ResourceContainer& resourceContainer)
	:Emerald(position, resourceContainer.textureManager(), resourceContainer.world())
{
}

Emerald::Emerald(sf::Vector2f position, TextureManager& textureManager, b2World& physicsWorld)
	:Entity(), mWorld(physicsWorld), Animatable(textureManager) 
{
	const auto EMERALD_SCALAR = 2.0F;
	
	loadAnimations();
	setAnimation(FILE_PATH + GEM_3);

	sf::IntRect& frame = mCurrentAnimation->frames[mCurrentFrame];
	sf::Texture* tex = mTextureManager.getTexture(mCurrentAnimation->textureKey);

	const int x = position.x, y = position.y;
	sf::IntRect physicsRect({ x, y }, frame.getSize());

	mpPhysicsBody = initPhysicsBody(physicsRect, mWorld, b2_staticBody, EMERALD_SCALAR, true);
	mpDrawable = initDrawable(frame, tex, position, false, EMERALD_SCALAR);

}

void Emerald::update(sf::Time dt)
{
	updateAnimation(dt);
}


void Emerald::loadAnimations()
{
	sf::Vector2i sizeInPixels(16, 16);
	loadAnimation(FILE_PATH + GEM_3, 7, 50.0f, sizeInPixels);
}

void Emerald::updateAnimation(sf::Time dt) 
{
	auto sprite = static_cast<sf::Sprite*>(mpDrawable);

	mAccumulator += dt.asMilliseconds();

	if (mAccumulator >= mCurrentAnimation->frameRate)
	{
		mCurrentFrame = (mCurrentFrame + 1) % mCurrentAnimation->frameCount;
		mAccumulator = 0.0f;
	}

	if (!sprite)
		throw std::runtime_error("Player does not have a sprite loaded");

	sf::Texture* tex = mTextureManager.getTexture(mCurrentAnimation->name);
	if (sprite->getTexture() != tex) // do not update if texture is the same
		sprite->setTexture(*tex);

	sf::IntRect frame = mCurrentAnimation->frames[mCurrentFrame];

	sprite->setTextureRect(frame);
}

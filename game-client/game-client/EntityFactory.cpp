#include "EntityFactory.h"

EntityFactory::EntityFactory(ResourceContainer& resourceContainer)
	:EntityFactory(resourceContainer.world(), resourceContainer.window(), resourceContainer.textureManger())
{}

EntityFactory::EntityFactory(b2World & world, sf::RenderWindow & window, TextureManager & textureManager)
	:mWindow(window), mTextureManager(textureManager), mWorld(world)
{}

Player* EntityFactory::createPlayer(sf::Vector2f position)
{
	return new Player(position, mTextureManager, mWorld);
}

Entity* EntityFactory::createBarrier(sf::IntRect rect)
{
	return new Entity(rect, mWorld, b2_staticBody);
}

Entity* EntityFactory::createMapTile(sf::Texture& tex, sf::IntRect& texRect, sf::Vector2f& position, float scalar)
{
	return new Entity(texRect, mWorld, b2_staticBody, false, &tex, position, sf::Color::Transparent, scalar);
}



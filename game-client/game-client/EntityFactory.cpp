#include "EntityFactory.h"

/**
 * @brief Construct a new Entity Factory:: Entity Factory object
 * 
 * @param resourceContainer ResourceContainer reference
 */
EntityFactory::EntityFactory(ResourceContainer& resourceContainer)
	:EntityFactory(resourceContainer.world(), resourceContainer.window(), resourceContainer.textureManager())
{}

/**
 * @brief Construct a new Entity Factory:: Entity Factory object
 * 
 * @param world physics world reference
 * @param window main window reference
 * @param textureManager texture manager reference
 */
EntityFactory::EntityFactory(b2World & world, sf::RenderWindow & window, TextureManager & textureManager)
	:mWindow(window), mTextureManager(textureManager), mWorld(world)
{}

/**
 * @brief Spawns a player at the unscaled x,y position
 * 
 * @param position unscaled x, y coordinates
 * @return Player* playable character entity
 */
Player* EntityFactory::createPlayer(sf::Vector2f position)
{
	auto player = new Player(position, mTextureManager, mWorld);
	player->setPhysicsBodyPtr(player);
	return player;
}

/**
 * @brief Spawns an emerald at the unscaled x,y position
 * 
 * @param position unscaled x, y coordinates
 * @return Emerald* entity
 */
Emerald* EntityFactory::createEmerald(sf::Vector2f position)
{
	auto emerald = new Emerald(position, mTextureManager, mWorld);
	emerald->setPhysicsBodyPtr(emerald);
	return emerald;
}

/**
 * @brief Spawns a chest at the unscaled x,y position
 * 
 * @param position unscaled x, y coordinates
 * @return Chest* chest entity
 */
Chest* EntityFactory::createChest(sf::Vector2f position)
{
	auto chest = new Chest(position, mTextureManager, mWorld);
	chest->setPhysicsBodyPtr(chest);
	return chest;
}

/**
 * @brief Spawns a barrier at the unscaled x,y position
 * 
 * @param position unscaled x, y coordinates
 * @return Entity* barrier entity
 */
Entity* EntityFactory::createBarrier(sf::IntRect rect)
{
	return new Entity(rect, mWorld, b2_staticBody);
}

/**
 * @brief Spawns a maptile at the unscaled x,y position
 * 
 * @param position unscaled x, y coordinates
 * @return Entity* map tile entity
 */
Entity* EntityFactory::createMapTile(sf::Texture& tex, sf::IntRect& texRect, sf::Vector2f& position, float scalar)
{
	return new Entity(texRect, mWorld, b2_staticBody, false, &tex, position, sf::Color::Transparent, scalar);
}



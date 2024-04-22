#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include "Player.h"
#include "ResourceContainer.h"

class EntityFactory
{
public:
	EntityFactory(ResourceContainer& resourceContainer);
	EntityFactory(b2World& world, sf::RenderWindow& window, TextureManager& textureManager);

	Player* createPlayer(sf::Vector2f position);
	Entity* createBarrier(sf::IntRect rect);
	Entity* createMapTile(sf::Texture& tex, sf::IntRect& texRect, sf::Vector2f& position, float scalar);
private:
	b2World& mWorld;
	sf::RenderWindow& mWindow;
	TextureManager& mTextureManager;
};
#endif // !ENTITY_FACTORY_H

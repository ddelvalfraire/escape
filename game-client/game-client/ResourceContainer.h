#ifndef RESOURCE_CONTAINER_H
#define RESOURCE_CONTAINER_H

#include <Box2D/Box2D.h>

#include "TextureManager.h"

class ResourceContainer
{
public:
	ResourceContainer(sf::RenderWindow& window);

	sf::RenderWindow& window();
	TextureManager& textureManager();
	b2World& world();
	
private:
	b2World mWorld;
	TextureManager mTextureManager;
	sf::RenderWindow& mWindow;
};
#endif // !RESOURCE_CONTAINER_H

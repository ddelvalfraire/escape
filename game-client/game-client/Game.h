#ifndef GAME_H
#define GAME_H

#include "TextureManager.h"
#include <Box2D/Box2D.h>
#include "Entity.h"

class Game
{
public:
	Game(sf::RenderWindow& window, TextureManager& textureManager);
	void run();

private:
	std::vector<Entity*> setUpLevel();
	void createWorldBoundaries(std::vector<Entity*> &entities);
	void pollEvents();

	b2World mWorld;
	sf::RenderWindow& mWindow;
	TextureManager& mTextureManager;
};
#endif // !GAME_H

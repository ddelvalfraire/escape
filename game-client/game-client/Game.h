#ifndef GAME_H
#define GAME_H

#include "ResourceContainer.h"
#include "Player.h"

class Game
{
public:
	Game(sf::RenderWindow& window, TextureManager& textureManager);
	void run();

private:
	std::vector<Entity*> setUpLevel();
	void createWorldBoundaries(std::vector<Entity*> &entities);
	void pollEvents();
	bool isInProximity(Entity* a, Entity* b);

	b2World mWorld;
	sf::RenderWindow& mWindow;
	TextureManager& mTextureManager;
};
#endif // !GAME_H

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
	void initializePhysicsWorld();
	std::vector<Entity*> setUpLevel();
	void pollEvents(Entity* player);
	void handleKeyboardInput(Entity* player);

	b2World mWorld;
	sf::RenderWindow& mWindow;
};
#endif // !GAME_H

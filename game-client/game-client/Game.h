#ifndef GAME_H
#define GAME_H

#include "ResourceContainer.h"

class Game
{
public:
	Game(sf::RenderWindow& window);
	void run();

private:
	void pollEvents();

	ResourceContainer mResourceContainer;
};
#endif // !GAME_H

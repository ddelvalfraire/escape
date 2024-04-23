#ifndef GAME_H
#define GAME_H

#include "ResourceContainer.h"
#include "Player.h"

class Game
{
public:
	Game(sf::RenderWindow& window);
	void run();

private:
	void pollEvents();
	void eventHandler(Player* player, std::vector<Entity*>& entities);
	bool isInProximity(Entity* a, Entity* b);

	ResourceContainer mResourceContainer;
};
#endif // !GAME_H

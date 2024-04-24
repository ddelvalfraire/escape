#ifndef GAME_H
#define GAME_H

#include "ResourceContainer.h"
#include "Player.h"

enum GameStatus
{
	InGame,
	Loss,
	Win
};
class Game
{
public:
	Game(sf::RenderWindow& window);
	void run();

private:
	void pollEvents();
	void handleWin();
	void handleLoss();

	float mElapsedTime;
	GameStatus mStatus;
	ResourceContainer mResourceContainer;
};
#endif // !GAME_H

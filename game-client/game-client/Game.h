#ifndef GAME_H
#define GAME_H

#include "ResourceContainer.h"
#include "Player.h"
#include "MenuAction.h"


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
	MenuAction run();

private:
	void handlePostGame();

	float mElapsedTime;
	GameStatus mStatus;
	ResourceContainer mResourceContainer;
};
#endif // !GAME_H

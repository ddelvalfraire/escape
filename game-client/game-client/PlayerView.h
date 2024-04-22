#ifndef PLAYER_VIEW_H
#define PLAYER_VIEW_H

#include "Player.h"
#include "Level.h"

class PlayerView : public sf::View
{
public:
	PlayerView(sf::RenderWindow& window, Player* player, TiledMapMetaData mapData);
	~PlayerView() = default;

	void update();
private:

	Player& mPlayer;
	sf::RenderWindow& mWindow;
	TiledMapMetaData mMapData;
};
#endif // !PLAYER_VIEW_H

#include "PlayerView.h"



PlayerView::PlayerView(sf::RenderWindow& window, Player* player, TiledMapMetaData mapData)
	:mWindow(window), mPlayer(*player), mMapData(mapData), View({0.0f, 0.0f, 1152, 648})
{}

void PlayerView::update()
{
    const sf::Vector2f pPos = mPlayer.getPosition(), size = mMapData.tiledMapSize;
    const float scale = mMapData.mapScaleFactor;
    const auto CAMERA_THRESHOLD = 100.f;

    sf::Vector2f scaledTiledMapSize(size.x * scale, size.y * scale);
    sf::FloatRect bounds(0.f, 0.f, scaledTiledMapSize.x, scaledTiledMapSize.y);

    sf::Vector2f newPos = getCenter();

    // handle x axis movement
    if (pPos.x < newPos.x - CAMERA_THRESHOLD)
        newPos.x = pPos.x + CAMERA_THRESHOLD;
    else if (pPos.x > newPos.x + CAMERA_THRESHOLD)
        newPos.x = pPos.x - CAMERA_THRESHOLD;

    // handle y axis movement
    if (pPos.y < newPos.y - CAMERA_THRESHOLD)
        newPos.y = pPos.y + CAMERA_THRESHOLD;
    else if (pPos.y > newPos.y + CAMERA_THRESHOLD)
        newPos.y = pPos.y - CAMERA_THRESHOLD;

    const sf::Vector2f halfView = getSize() / 2.0f;

    const float minXBounds = std::min(newPos.x, bounds.width - halfView.x);
    const float minYBounds = std::min(newPos.y, bounds.height - halfView.y);

    // make sure we dont expose a black background 
    newPos.x = std::max(halfView.x, minXBounds);
    newPos.y = std::max(halfView.y, minYBounds);

    setCenter(newPos);
}


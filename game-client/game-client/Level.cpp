#include "Level.h"


Level::Level(const std::string& tmxFile, sf::Vector2f playerPosition, ResourceContainer& resourceContainer)
	:Level(tmxFile,playerPosition, resourceContainer.window(), resourceContainer.world(), resourceContainer.textureManager())
{}

Level::Level(const std::string & tmxFile,sf::Vector2f playerPosition, sf::RenderWindow & window, b2World& world, TextureManager & textureManager)
	:mTmxFile(tmxFile), mWindow(window), mWorld(world), playerInitialPosition(playerPosition), entityFactory(world, window, textureManager) 
{

	loadTmxMap();
	createWorldBoundaries();
	mPlayer = entityFactory.createPlayer(playerPosition);
	mEntities.push_back(mPlayer);

}


Player* Level::player()
{
	return mPlayer;
}

const std::vector<Entity*>& Level::entities()
{
	return mEntities;
}

TiledMapMetaData Level::metaData()
{
	return mMapMetaData;
}

/**
 * @brief routine for tmx file loading based on mTmxFile
 * 
 */
void Level::loadTmxMap()
{
	tmx::Map map;

	if (!map.load(mTmxFile))
		throw std::runtime_error("Could not load tmx file");
	
	saveMapMetaData(map);
	parseTilesets(map);
	parseLayers(map);


}

void Level::saveMapMetaData(const tmx::Map& map)
{
	mMapMetaData.mapScaleFactor = calculateScalar(map);
	const float width = map.getTileSize().x * map.getTileCount().x;
	const float height = map.getTileSize().y * map.getTileCount().y;

	mMapMetaData.tiledMapSize = { 
		width,
		height
	};
}



/**
 * @brief Iterates through a tilesets and creates their textures and text rects
 * 
 * @param map tmxMap to parse from
 */
void Level::parseTilesets(const tmx::Map &map)
{
	uint32_t tileCount = 1;

	for (const auto& tileset : map.getTilesets())
	{
		for (const auto& tile : tileset.getTiles())
		{
			sf::Texture* tex;

			if (mTextureManager.hasTexture(tile.imagePath))
				tex = mTextureManager.getTexture(tile.imagePath);
			else
				tex = mTextureManager.loadTexture(tile.imagePath);

			sf::IntRect* textRec = getTileTextureRect(tile.imagePosition, tile.imageSize);
			std::pair<sf::IntRect*, sf::Texture*> pair = { textRec, tex };
			mTileMap.emplace(tileCount++, pair);
		}

	}
}

/**
 * @brief Parses the layers of a tmx file and creates their sprites and entities
 * 
 * @param map 
 */
void Level::parseLayers(const tmx::Map &map)
{
	const auto& layer = map.getLayers()[1];

	if (layer->getType() != tmx::Layer::Type::Tile)
		throw std::runtime_error("this is not a valid layer");

	const auto& tileLayer = layer->getLayerAs<tmx::TileLayer>();
	const std::vector<tmx::TileLayer::Tile>& tiles = tileLayer.getTiles();

	// for of loop does not work here for some reason
	for (size_t tileNumber = 0; tileNumber < tiles.size(); ++tileNumber) 
	{
		const tmx::TileLayer::Tile& tile = tiles[tileNumber];

		if (tile.ID == 0)
			continue;

		const auto& pair = mTileMap.at(tile.ID);
		
		const auto scalar = mMapMetaData.mapScaleFactor;

		sf::Vector2f position = extrapolateTilePosition(map, tileLayer, tileNumber, scalar);

		auto entity = entityFactory.createMapTile(*pair.second, *pair.first, position, scalar);

		mEntities.push_back(entity);
	}
}

void Level::createWorldBoundaries()
{
	const int WINDOW_WIDTH = mWindow.getSize().x;
	const int WINDOW_HEIGHT = mWindow.getSize().y;

	auto left = entityFactory.createBarrier({ {-10, WINDOW_HEIGHT / 2 }, {20, WINDOW_HEIGHT} });
	auto right = entityFactory.createBarrier({ {WINDOW_WIDTH + 10, WINDOW_HEIGHT / 2}, {20, WINDOW_HEIGHT} });
	auto ground = entityFactory.createBarrier({ {WINDOW_WIDTH / 2, WINDOW_HEIGHT - 10}, {WINDOW_WIDTH, 20} });


	mEntities.push_back(left);
	mEntities.push_back(right);
	mEntities.push_back(ground);

}

/**
 * @brief calculates the x y coordinates of a tile based on window and map size
 * 
 * @param map 
 * @param currentLayer 
 * @param currentTileNumber 
 * @param scalar 
 * @return sf::Vector2f 
 */
sf::Vector2f Level::extrapolateTilePosition(const tmx::Map& map, const tmx::TileLayer &currentLayer, const size_t currentTileNumber, const float scalar)
{
	const tmx::Vector2u& numTiles = map.getTileCount();
	const tmx::Vector2u& tileSize = map.getTileSize();
	
	const tmx::Vector2i& layerOffset = currentLayer.getOffset();

	const auto row = (currentTileNumber % numTiles.x) * tileSize.x * scalar - layerOffset.x * scalar;
	const auto col = (currentTileNumber / numTiles.x) * tileSize.y * scalar - layerOffset.y * scalar;

	return sf::Vector2f(row, col);
}

/**
 * @brief calculates a sprite scalar based on window size
 * 
 * @param map tmxMap to derive tilecount and tilesize
 * @return const float the appropriate scalar based on window size and map size
 */
const float Level::calculateScalar(const tmx::Map& map)
{
	const tmx::Vector2u& numTiles = map.getTileCount();
	const tmx::Vector2u& tileSize = map.getTileSize();

	const sf::Vector2f mapSize(numTiles.x * tileSize.x, numTiles.y * tileSize.y);
	const sf::Vector2u& winSize = mWindow.getSize();

	return std::min(winSize.x / mapSize.x, winSize.y / mapSize.y);
}

/**
 * @brief converts a tmx::Vector2u position and size to sf:IntRect for a texture
 * 
 * @param position 
 * @param size 
 * @return sf::IntRect* 
 */
sf::IntRect* Level::getTileTextureRect(const tmx::Vector2u& position, const tmx::Vector2u& size)
{
	const auto posX = static_cast<int>(position.x);
	const auto posY = static_cast<int>(position.y);
	const auto sizeX = static_cast<int>(size.x);
	const auto sizeY = static_cast<int>(size.y);

	return new sf::IntRect(posX, posY, sizeX, sizeY);
	
}

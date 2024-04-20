#include "Level.h"

Level::Level(const std::string& tmxFile, TextureManager& textureManager, sf::RenderWindow& window)
	: mTmxFile(tmxFile), mTextureManager(textureManager), mWindow(window) {}

Level::~Level()
{
}

const std::vector<sf::Sprite*>& Level::sprites()
{
	return mSprites;
}

void Level::loadTmxMap()
{
	tmx::Map map;
	if (!map.load(mTmxFile))
		throw std::runtime_error("Could not load tmx file");
	
	parseTilesets(map);
	parseLayers(map);
}

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

void Level::parseLayers(const tmx::Map &map)
{
	
	for (const auto& layer : map.getLayers())
	{
		if (layer->getType() != tmx::Layer::Type::Tile)
			continue;
		
		const auto& tileLayer = layer->getLayerAs<tmx::TileLayer>();
		const auto& tiles = tileLayer.getTiles();
		

		size_t tileNumber = 0;
		for (const auto& tile : tiles)
		{
			if (tile.ID == 0)
				continue;

			auto& pair = mTileMap.at(tile.ID);

			auto sprite = new sf::Sprite(*pair.second, *pair.first);

			const float scalar = calculateScalar(map);
			sprite->setScale(scalar, scalar);

			sf::Vector2f position = extrapolateTilePosition(map, tileLayer, tileNumber, scalar);
			sprite->setPosition(position);

			mSprites.push_back(sprite);
		}
	}
}

sf::Vector2f Level::extrapolateTilePosition(const tmx::Map& map, const tmx::TileLayer &currentLayer, const size_t tileNumber, const float scalar)
{
	const tmx::Vector2u& numTiles = map.getTileCount();
	const tmx::Vector2u& tileSize = map.getTileSize();
	
	const tmx::Vector2i& layerOffset = currentLayer.getOffset();

	const float row = (tileNumber % numTiles.x) * tileSize.x * scalar - layerOffset.x * scalar;
	const float col = (tileNumber / numTiles.x) * tileSize.y * scalar - layerOffset.y * scalar;

	return sf::Vector2f(row, col);
}

const float Level::calculateScalar(const tmx::Map& map)
{
	const tmx::Vector2u& numTiles = map.getTileCount();
	const tmx::Vector2u& tileSize = map.getTileSize();

	const sf::Vector2f mapSize(numTiles.x * tileSize.x, numTiles.y * tileSize.y);
	const sf::Vector2u& winSize = mWindow.getSize();

	return std::min(winSize.x / mapSize.x, winSize.y / mapSize.y);
}

sf::IntRect* Level::getTileTextureRect(const tmx::Vector2u& position, const tmx::Vector2u& size)
{
	const auto posX = static_cast<int>(position.x);
	const auto posY = static_cast<int>(position.y);
	const auto sizeX = static_cast<int>(size.x);
	const auto sizeY = static_cast<int>(size.y);

	return new sf::IntRect(posX, posY, sizeX, sizeY);

	
}

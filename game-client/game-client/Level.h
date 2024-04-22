#ifndef LEVEL_H
#define LEVEL_H

#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include <SFML/Graphics.hpp>

#include "EntityFactory.h"
#include "ResourceContainer.h"

using TileMap = std::unordered_map <uint32_t, std::pair<sf::IntRect*, sf::Texture*>>;

struct TiledMapMetaData
{
	sf::Vector2f tiledMapSize;
	float mapScaleFactor;
};

class Level
{
public:

	Level(const std::string& tmxFile, sf::Vector2f playerPosition, ResourceContainer& resourceContainer);
	Level(const std::string& tmxFile,sf::Vector2f playerPosition, sf::RenderWindow &window, b2World& world, TextureManager& textureManager);

	~Level() = default;

	Player* player();
	const std::vector<Entity*>& entities();
	TiledMapMetaData metaData();
	
private:
	void loadTmxMap();
	void saveMapMetaData(const tmx::Map &map);
	void parseTilesets(const tmx::Map &map);
	void parseLayers(const tmx::Map &map);
	void createWorldBoundaries();
	sf::Vector2f extrapolateTilePosition(const tmx::Map &map, const tmx::TileLayer &currentLayer, const size_t tileNumber, const float scalar);
	const float calculateScalar(const tmx::Map& map);
	sf::IntRect* getTileTextureRect(const tmx::Vector2u& position, const tmx::Vector2u& size);



	TiledMapMetaData mMapMetaData;
	sf::Vector2f playerInitialPosition;
	Player* mPlayer;
	std::string mTmxFile;
	TileMap mTileMap;
	std::vector<Entity*> mEntities;
	EntityFactory entityFactory;
	TextureManager mTextureManager;
	b2World& mWorld;
	sf::RenderWindow& mWindow;
};

#endif // !LEVEL_H

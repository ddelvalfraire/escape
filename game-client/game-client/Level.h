#ifndef LEVEL_H
#define LEVEL_H

#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include <SFML/Graphics.hpp>

#include "TextureManager.h"

using TileMap = std::unordered_map <uint32_t, std::pair<sf::IntRect*, sf::Texture*>>;

class Level
{
public:
	Level(const std::string &tmxFile, sf::RenderWindow &window);
	~Level() = default;

	const std::vector<sf::Sprite*>& sprites();
	
private:
	void loadTmxMap();
	void parseTilesets(const tmx::Map &map);
	void parseLayers(const tmx::Map &map);
	sf::Vector2f extrapolateTilePosition(const tmx::Map &map, const tmx::TileLayer &currentLayer, const size_t tileNumber, const float scalar);
	const float calculateScalar(const tmx::Map& map);
	sf::IntRect* getTileTextureRect(const tmx::Vector2u& position, const tmx::Vector2u& size);


	std::string mTmxFile;
	TileMap mTileMap;
	std::vector<sf::Sprite*> mSprites;
	TextureManager mTextureManager;
	sf::RenderWindow& mWindow;
};

#endif // !LEVEL_H

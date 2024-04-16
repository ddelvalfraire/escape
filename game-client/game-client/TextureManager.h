#ifndef TEXTURE_MANAGER
#define TEXTURE_MANAGER

#include <SFML/Graphics.hpp>
#include <unordered_map>

constexpr auto LEVER_TEXTURE = "lever.png";
constexpr auto PLAYER_TEXTURE = "player.png";

class TextureManager
{
public:
	TextureManager() = default;
	~TextureManager() = default;

	void loadTexture(const char* fileName);
	sf::Texture& getTexture(const char* fileName);
	void deleteTexture(const char* filename);

private:
	std::unordered_map<const char*, sf::Texture> mTextures;
};

#endif // !TEXTURE_MANAGER



#include "TextureManager.h"

/**
 * @brief Loads a texture from a file
 *
 * @param fileName filepath of your texture
 */
void TextureManager::loadTexture(const std::string &fileName)
{
	auto tex = new sf::Texture;
	mTextures.emplace(fileName, tex);

	if (!tex->loadFromFile(fileName))
	{
		throw std::runtime_error("Texture file does not exist");
	}
}

/**
 * @brief retrieves a texture object via the filepath of the texture
 *
 * @param fileName filepath of the texture
 * @return sf::Texture& reference to the texture object with the corresponding file
 */
sf::Texture* TextureManager::getTexture(const std::string& fileName)
{
	auto it = mTextures.find(fileName);

	if (it != mTextures.end())
	{
		return it->second;
	}

	throw std::runtime_error("Attempting to fetch a non exisitant texture");
}

/**
 * @brief removes and destroys a texture object by filename
 *
 * @param filename original filepath used to instantiate the texture object
 */
void TextureManager::deleteTexture(const std::string& fileName)
{
	mTextures.erase(fileName);
}

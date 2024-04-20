#include "TextureManager.h"

/**
 * @brief deletes all of the allocated textures in the texture map
 *
 */
TextureManager::~TextureManager()
{
	for (auto& pair : mTextures)
		delete pair.second;
}

/**
 * @brief Loads a texture from a file
 *
 * @param fileName filepath of your texture
 */
sf::Texture* TextureManager::loadTexture(const std::string &fileName)
{
	auto tex = new sf::Texture;
	mTextures.emplace(fileName, tex);

	if (!tex->loadFromFile(fileName))
		throw std::runtime_error("Texture file does not exist");
	
	return tex;
}

/**
 * @brief retrieves a texture object via the filepath of the texture
 *
 * @param fileName filepath of the texture
 * @return sf::Texture& reference to the texture object with the corresponding file
 */
sf::Texture* TextureManager::getTexture(const std::string& fileName)
{
	if (hasTexture(fileName))
		return mTextures.at(fileName);

	throw std::runtime_error("Attempting to fetch a non exisitant texture");
}

bool TextureManager::hasTexture(const std::string& fileName)
{
	return mTextures.find(fileName) != mTextures.end();
}

/**
 * @brief removes and destroys a texture object by filename
 *
 * @param filename original filepath used to instantiate the texture object
 */
void TextureManager::deleteTexture(const std::string& fileName)
{
	if (hasTexture(fileName))
		mTextures.erase(fileName);
}
